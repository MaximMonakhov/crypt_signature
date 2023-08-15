import 'package:crypt_signature/src/models/certificate.dart';
import 'package:crypt_signature/src/models/pkcs7.dart';
import 'package:crypt_signature/src/utils/extensions/extensions.dart';

/// Результат подписи
class SignResult {
  /// Сертификат из контейнера с приватным ключем
  final Certificate certificate;

  /// Подписываемый хэш
  final String digest;

  /// Сигнатура
  final String signature;

  /// Алгоритм сигнатуры
  final String signatureAlgorithm;

  SignResult(this.certificate, {required this.digest, required this.signature, required this.signatureAlgorithm});

  SignResult.from(SignResult other)
      : certificate = other.certificate,
        digest = other.digest,
        signature = other.signature,
        signatureAlgorithm = other.signatureAlgorithm;

  @override
  String toString() {
    StringBuffer stringBuffer = StringBuffer()
      ..writeln("SignResult")
      ..writeln("Сертификат из контейнера с приватным ключем: ${certificate.certificate.truncate()}")
      ..writeln("Digest: ${digest.truncate()}")
      ..writeln("Signature: ${signature.truncate()}")
      ..writeln("Алгоритм сигнатуры: $signatureAlgorithm");

    return stringBuffer.toString();
  }
}

class PKCS7SignResult extends SignResult {
  final PKCS7 pkcs7;

  /// Хэш от изначального сообщения. Так как в signResult лежит хэш от атрибутов подписи
  final String initialDigest;

  PKCS7SignResult(
    this.pkcs7,
    super.certificate, {
    required this.initialDigest,
    required super.digest,
    required super.signature,
    required super.signatureAlgorithm,
  });

  PKCS7SignResult.from(this.pkcs7, SignResult signResult, {required this.initialDigest}) : super.from(signResult);

  @override
  String toString() => "${super.toString()}\nPKCS7: $pkcs7\nInitialDigest: $initialDigest";
}
