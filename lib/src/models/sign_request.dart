import 'dart:async';

import 'package:crypt_signature/crypt_signature.dart';
import 'package:crypt_signature/src/native/native.dart';

typedef Signer<T extends SignResult> = Future<T> Function(Certificate certificate, String password);

abstract class SignRequest<T extends SignResult> {
  Signer<T> get signer;
}

class MessageSignRequest extends SignRequest {
  final String message;

  /// Высчитывает хэш от сообщения и подписывает его.
  ///
  /// Возвращает объект [SignResult], который содержит результат подписи в формате Base64.
  MessageSignRequest(this.message);

  @override
  Signer get signer => (certificate, password) async {
        DigestResult digestResult = await Native.digest(certificate, password, message);
        return Native.sign(certificate, password, digestResult.digest);
      };
}

/// Создание подписи по стандарту CMS.
abstract class CMSSignRequest extends SignRequest<CMSSignResult> {
  /// Получение хэша:
  /// * Для [CMSMessageSignRequest] создается на месте из сообщения.
  /// * Для [CMSHashSignRequest] получается из вне.
  Future<String> _getDigest(Certificate certificate, String password);

  /// Создание PKCS#7
  PKCS7 _createPKCS7(Certificate certificate, String digest, String certificateDigest, {String? message}) =>
      PKCS7(certificate, digest, certificateDigest, message: message);

  @override
  Signer<CMSSignResult> get signer => (Certificate certificate, String password) async {
        String digest = await _getDigest(certificate, password);
        String certificateDigest = (await Native.digest(certificate, password, certificate.certificate)).digest;
        PKCS7 pkcs7 = _createPKCS7(certificate, digest, certificateDigest);
        String signedAttributes = pkcs7.signerInfo.signedAttribute.message;
        DigestResult signedAttributesDigest = await Native.digest(certificate, password, signedAttributes);
        SignResult signResult = await Native.sign(certificate, password, signedAttributesDigest.digest);
        pkcs7.signerInfo.attachSignature(signResult.signature);
        return CMSSignResult.from(pkcs7, signResult, initialDigest: digest);
      };
}

class CMSMessageSignRequest extends CMSSignRequest {
  /// Формат подписи (DETACHED/ATTACHED).
  final bool detached;

  /// Формирование сообщения на основе выбранного пользователем сертификата.
  final Future<String> Function(Certificate certificate) getMessage;

  /// Создание подписи по стандарту CMS.
  ///
  /// Возвращает объект [CMSSignResult], который содержит [PKCS7] как результат подписи.
  CMSMessageSignRequest(this.getMessage, {this.detached = true});

  /// Изначальное сообщение. Сохраняется для вставки в PKCS#7 для случая External Digest.
  String? _message;

  @override
  PKCS7 _createPKCS7(certificate, digest, certificateDigest, {message}) =>
      super._createPKCS7(certificate, digest, certificateDigest, message: detached ? null : _message);

  @override
  Future<String> _getDigest(Certificate certificate, String password) async {
    _message = await getMessage(certificate);
    DigestResult digestResult = await Native.digest(certificate, password, _message!);
    return digestResult.digest;
  }
}

class CMSHashSignRequest extends CMSSignRequest {
  /// Формирование хэша на основе выбранного пользователем сертификата.
  final Future<String> Function(Certificate certificate) getHash;

  /// Создание подписи по стандарту CMS, но с использованием уже готового хэша от сообщения (External Digest).
  ///
  /// Возвращает объект [CMSSignResult], который содержит [PKCS7] как результат подписи.
  CMSHashSignRequest(this.getHash);

  @override
  Future<String> _getDigest(Certificate certificate, String password) => getHash(certificate);
}

/// Класс для своей логики подписи.
class CustomSignRequest<T extends SignResult> extends SignRequest<T> {
  /// Вызывается при выборе сертификата, пользовательская логика подписи.
  final Signer<T> onCertificateSelected;

  CustomSignRequest(this.onCertificateSelected);

  @override
  Signer<T> get signer => onCertificateSelected;
}
