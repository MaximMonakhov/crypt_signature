import 'dart:async';

import 'package:crypt_signature/crypt_signature.dart';
import 'package:crypt_signature/src/native/native.dart';

typedef Signer<T extends SignResult> = Future<T> Function(Certificate certificate, String password);

abstract class SignRequest<T extends SignResult> {
  Signer<T> get signer;
}

/// Класс для получение сигнатуры от сообщения
class MessageSignRequest extends SignRequest {
  final String message;

  MessageSignRequest(this.message);

  @override
  Signer get signer => (certificate, password) async {
        DigestResult digestResult = await Native.digest(certificate, password, message);
        return Native.sign(certificate, password, digestResult.digest);
      };
}

abstract class PKCS7SignRequest extends SignRequest<PKCS7SignResult> {
  /// Получения digest для подписи
  /// * Для [PKCS7MessageSignRequest] создается на месте из сообщения
  /// * Для [PKCS7HASHSignRequest] получается из вне
  Future<String> _getDigest(Certificate certificate, String password);

  @override
  Signer<PKCS7SignResult> get signer => (Certificate certificate, String password) async {
        String digest = await _getDigest(certificate, password);
        String certificateDigest = (await Native.digest(certificate, password, certificate.certificate)).digest;
        PKCS7 pkcs7 = PKCS7(certificate, digest, certificateDigest);
        String signedAttributes = pkcs7.signerInfo.signedAttribute.message;
        DigestResult signedAttributesDigest = await Native.digest(certificate, password, signedAttributes);
        SignResult signResult = await Native.sign(certificate, password, signedAttributesDigest.digest);
        pkcs7.signerInfo.attachSignature(signResult.signature);
        return PKCS7SignResult.from(pkcs7, signResult, initialDigest: digest);
      };
}

/// Класс для получения сигнатуры от хэша аттрибутов подписи PKCS7 на основе сообщения
/// * Получает сообщение [getMessage] на основе выбранного сертификата
/// * Высчитывает хэш от сообщения
/// * Формирует PKCS7 и атрибуты подписи
/// * Высчитывает хэш от атрибутов подписи
/// * Подписание атрибутов подписи
/// * Вставка сигнатуры в PKCS7
class PKCS7MessageSignRequest extends PKCS7SignRequest {
  /// Получения изначального сообщения
  final Future<String> Function(Certificate certificate) getMessage;

  PKCS7MessageSignRequest(this.getMessage);

  @override
  Future<String> _getDigest(Certificate certificate, String password) async {
    String message = await getMessage(certificate);
    DigestResult digestResult = await Native.digest(certificate, password, message);
    return digestResult.digest;
  }
}

/// Класс для получения сигнатуры от хэша аттрибутов подписи PKCS7 на основе хэша сообщения.
/// Работает как [PKCS7MessageSignRequest], но не высчитывает хэш от изначального сообщения
class PKCS7HASHSignRequest extends PKCS7SignRequest {
  /// Получения хэша сообщения
  final Future<String> Function(Certificate certificate) getHash;

  PKCS7HASHSignRequest(this.getHash);

  @override
  Future<String> _getDigest(Certificate certificate, String password) => getHash(certificate);
}

/// Класс для своей логики подписи
class CustomSignRequest<T extends SignResult> extends SignRequest<T> {
  /// Вызывается при выборе сертификата, пользовательская логика подписи
  final Signer<T> onCertificateSelected;

  CustomSignRequest(this.onCertificateSelected);

  @override
  Signer<T> get signer => onCertificateSelected;
}
