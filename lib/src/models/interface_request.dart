import 'dart:async';
import 'dart:io';

import 'package:crypt_signature/crypt_signature.dart';
import 'package:crypt_signature/src/models/xml_dsig/request/xml_operations.dart';
import 'package:crypt_signature/src/models/xml_dsig/xml_signer.dart';
import 'package:crypt_signature/src/native/native.dart';
import 'package:xml/xml.dart';

typedef Signer<T extends SignResult> = Future<T> Function(Certificate certificate, String password);

abstract class InterfaceRequest<T extends SignResult> {
  Signer get signer;
}

/// Класс для получение сигнатуры от сообщения
class MessageInterfaceRequest extends InterfaceRequest {
  final String message;

  MessageInterfaceRequest(this.message);

  @override
  Signer get signer => (certificate, password) async {
        DigestResult digestResult = await Native.digest(certificate, password, message);
        return Native.sign(certificate, password, digestResult.digest);
      };
}

abstract class PKCS7InterfaceRequest extends InterfaceRequest<PKCS7SignResult> {
  /// Получение аттрибутов подписи на основе [digest] сообщения
  final Future<String> Function(Certificate certificate, String digest)? getSignedAttributes;

  /// Получения digest для подписи
  /// * Для [PKCS7MessageInterfaceRequest] создается на месте из сообщения
  /// * Для [PKCS7HASHInterfaceRequest] получается из вне
  Future<String> _getDigest(Certificate certificate, String password);

  PKCS7InterfaceRequest({this.getSignedAttributes});

  @override
  Signer get signer => Platform.isAndroid ? androidSigner : iosSigner;

  Signer get androidSigner => (Certificate certificate, String password) async {
        String digest = await _getDigest(certificate, password);
        PKCS7 pkcs7 = await Native.createPKCS7(certificate, password, digest);
        String signedAttributes = pkcs7.signedAttributes;
        DigestResult signedAttributesDigest = await Native.digest(certificate, password, signedAttributes);
        SignResult signResult = await Native.sign(certificate, password, signedAttributesDigest.digest);
        pkcs7 = await Native.addSignatureToPKCS7(pkcs7, signResult.signature);
        return PKCS7SignResult.from(PKCS7(content: pkcs7.content, signedAttributes: signedAttributes), signResult, initialDigest: digest);
      };

  Signer get iosSigner => (Certificate certificate, String password) async {
        assert(getSignedAttributes != null);
        String digest = await _getDigest(certificate, password);
        String signedAttributes = await getSignedAttributes!(certificate, digest);
        DigestResult signedAttributesDigest = await Native.digest(certificate, password, signedAttributes);
        SignResult signResult = await Native.sign(certificate, password, signedAttributesDigest.digest);
        return PKCS7SignResult.from(PKCS7(content: "", signedAttributes: signedAttributes), signResult, initialDigest: digest);
      };
}

/// Класс для получения сигнатуры от хэша аттрибутов подписи PKCS7 на основе сообщения
/// * Получает сообщение [getMessage] на основе выбранного сертификата
/// * Высчитывает хэш от сообщения
/// * Формирует PKCS7 и атрибуты подписи (для iOS не реализовано, используется метод [getSignedAttributes])
/// * Высчитывает хэш от атрибутов подписи
/// * Подписание атрибутов подписи
/// * Вставка сигнатуры в PKCS7
class PKCS7MessageInterfaceRequest extends PKCS7InterfaceRequest {
  /// Получения изначального сообщения
  final Future<String> Function(Certificate certificate) getMessage;

  PKCS7MessageInterfaceRequest(this.getMessage, {super.getSignedAttributes});

  @override
  Future<String> _getDigest(Certificate certificate, String password) async {
    String message = await getMessage(certificate);
    DigestResult digestResult = await Native.digest(certificate, password, message);
    return digestResult.digest;
  }
}

/// Класс для получения сигнатуры от хэша аттрибутов подписи PKCS7 на основе хэша сообщения.
/// Работает как [PKCS7MessageInterfaceRequest], но не высчитывает хэш от изначального сообщения
class PKCS7HASHInterfaceRequest extends PKCS7InterfaceRequest {
  /// Получения хэша сообщения
  final Future<String> Function(Certificate certificate) getHash;

  PKCS7HASHInterfaceRequest(this.getHash, {super.getSignedAttributes});

  @override
  Future<String> _getDigest(Certificate certificate, String password) => getHash(certificate);
}

/// Класс для своей логики подписи
class CustomInterfaceRequest<T extends SignResult> extends InterfaceRequest<T> {
  /// Вызывается при выборе сертификата, пользовательская логика подписи
  final Signer onCertificateSelected;

  CustomInterfaceRequest(this.onCertificateSelected);

  @override
  Signer get signer => onCertificateSelected;
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
class XMLInterfaceRequest extends InterfaceRequest<XMLDSIGSignResult> {
  XMLInterfaceRequest(
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

  factory XMLInterfaceRequest.rawDocument(
    FutureOr<String> Function(Certificate certificate) getRawDocument, {
    XmlSignOptions? options,
  }) {
    FutureOr<XmlDocument> getDocument(Certificate certificate) async {
      final String rawDocument = await getRawDocument(certificate);
      return XmlDocument.parse(rawDocument);
    }

    return XMLInterfaceRequest(getDocument, options: options);
  }

  late XmlSigner _signer;

  @override
  Signer<XMLDSIGSignResult> get signer => _signer.sign;
}
