import 'package:crypt_signature/models/certificate.dart';

abstract class InterfaceRequest {}

/// Класс для получение сигнатуры от сообщения
class MessageInterfaceRequest extends InterfaceRequest {
  final String message;

  MessageInterfaceRequest(this.message);
}

/// Класс для получения сигнатуры от хэша аттрибутов подписи PKCS7 на основе сообщения
/// * Получает сообщение ([getMessage]) на основе выбранного сертификата
/// * Высчитывает хэш от сообщения
/// * Формирует PKCS7 и атрибуты подписи (для iOS не реализовано, используется метод [getSignedAttributes])
/// * Высчитывает хэш от атрибутов подписи
/// * Подписание атрибутов подписи
/// * Вставка сигнатуры в PKCS7
class PKCS7InterfaceRequest extends InterfaceRequest {
  /// Получения изначального сообщения
  final Future<String> Function(Certificate certificate) getMessage;

  /// Получение аттрибутов подписи на основе [digest] сообщения
  final Future<String> Function(Certificate certificate, String digest) getSignedAttributes;

  PKCS7InterfaceRequest(this.getMessage, {this.getSignedAttributes});
}

/// Класс для получения сигнатуры от хэша аттрибутов подписи PKCS7 на основе хэша сообщения
/// Работает как [PKCS7InterfaceRequest], но не высчитывает хэш от изначального сообщения
class PKCS7HASHInterfaceRequest extends InterfaceRequest {
  /// Получения хэша сообщения
  final Future<String> Function(Certificate certificate) getDigest;

  /// Получение аттрибутов подписи на основе [digest] сообщения
  final Future<String> Function(Certificate certificate, String digest) getSignedAttributes;

  PKCS7HASHInterfaceRequest(this.getDigest, {this.getSignedAttributes});
}

/// Класс для своей логики подписи
class CustomInterfaceRequest extends InterfaceRequest {
  /// Вызывается при выборе сертификата
  final Future<void> Function(Certificate certificate, String password) onCertificateSelected;

  CustomInterfaceRequest(this.onCertificateSelected);
}
