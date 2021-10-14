import 'certificate.dart';

/// Результат подписи
class SignResult {
  /// Сертификат из контейнера с приватным ключем
  final Certificate certificate;

  /// Подписываемые данные
  final String data;

  /// Сигнатура
  final String signature;

  SignResult(this.certificate, this.data, this.signature);
}