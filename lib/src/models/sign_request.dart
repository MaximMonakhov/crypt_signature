import 'dart:async';

import 'package:crypt_signature/crypt_signature.dart';
import 'package:crypt_signature/src/models/xml_dsig/request/xml_operations.dart';
import 'package:crypt_signature/src/models/xml_dsig/xml_signer.dart';
import 'package:crypt_signature/src/native/native.dart';
import 'package:xml/xml.dart';

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

  /// Создание PKCS7
  PKCS7 _createPKCS7(Certificate certificate, String digest, String certificateDigest, {String? message}) =>
      PKCS7(certificate, digest, certificateDigest, message: message);

  @override
  Signer<PKCS7SignResult> get signer => (Certificate certificate, String password) async {
        String digest = await _getDigest(certificate, password);
        String certificateDigest = (await Native.digest(certificate, password, certificate.certificate)).digest;
        PKCS7 pkcs7 = _createPKCS7(certificate, digest, certificateDigest);
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
  /// Изначальное сообщение
  late final String message;

  /// Формат подписи (DETACHED/ATTACHED)
  final bool detached;

  /// Получения изначального сообщения
  final Future<String> Function(Certificate certificate) getMessage;

  PKCS7MessageSignRequest(this.getMessage, {this.detached = true});

  @override
  PKCS7 _createPKCS7(certificate, digest, certificateDigest, {message}) =>
      super._createPKCS7(certificate, digest, certificateDigest, message: detached ? null : this.message);

  @override
  Future<String> _getDigest(Certificate certificate, String password) async {
    message = await getMessage(certificate);
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

/// Подписывает xml - документ по стандарту `XmlDSig`
/// * Функция [getDocument] возвращает документ
/// * `XmlElementResolver` находит целевой узел в документе
/// * В зависимости от типа подписи выполняются предварительные преобразования
/// * На последнем этапе целевой узел подвергается канонизации
/// * На основании выбранного [certificate] определяются алгоритмы хеширования и подписи
/// * От целевого узла вычисляется хэш и формируется узел `SignedInfo`
/// * `SignedInfo` канонизируется и подвергается подписи (хэш + подпись)
/// * В зависимости от типа подписи формируется результат подписи
class XMLSignRequest extends SignRequest<XMLDSIGSignResult> {
  XMLSignRequest(
    FutureOr<XmlDocument> Function(Certificate certificate) getDocument, {
    XmlSignOptions? options,
  }) {
    final XmlSignOptions targetOptions = options ?? XmlSignOptions();
    _signer = XmlSigner(
      getDocument,
      targetOptions,
      XmlOperations.fromOptions(targetOptions),
    );
  }

  factory XMLSignRequest.rawDocument(
    FutureOr<String> Function(Certificate certificate) getRawDocument, {
    XmlSignOptions? options,
  }) {
    FutureOr<XmlDocument> getDocument(Certificate certificate) async {
      final String rawDocument = await getRawDocument(certificate);
      return XmlDocument.parse(rawDocument);
    }

    return XMLSignRequest(getDocument, options: options);
  }

  late XmlSigner _signer;

  @override
  Signer<XMLDSIGSignResult> get signer => _signer.sign;
}
