import 'package:crypt_signature/models/certificate.dart';

/// Результат хэширования
class DigestResult {
  /// Сертификат из контейнера с приватным ключем
  final Certificate certificate;

  /// Подписываемые данные
  final String message;

  /// Хэш
  final String digest;

  /// Алгоритм хэширования
  final String digestAlgorithm;

  DigestResult({this.certificate, this.message, this.digest, this.digestAlgorithm});
}
