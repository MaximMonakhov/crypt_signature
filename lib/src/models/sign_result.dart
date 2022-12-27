import 'dart:convert';
import 'dart:io';

import 'package:crypt_signature/src/models/certificate.dart';
import 'package:crypt_signature/src/models/pkcs7.dart';
import 'package:crypt_signature/src/utils/extensions.dart';

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

  SignResult(this.certificate, {required this.digest, required String signature, required this.signatureAlgorithm})
      : // Нативные функции win32 возвращают развернутую сигнатуру
        signature = Platform.isIOS ? reverseSignature(signature) : signature;

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

  static String reverseSignature(String signature) => base64.encode(base64.decode(signature.replaceAll("\n", "")).reversed.toList());
}

class PKCS7SignResult extends SignResult {
  final PKCS7 pkcs7;

  PKCS7SignResult(this.pkcs7, super.certificate, {required super.digest, required super.signature, required super.signatureAlgorithm});

  PKCS7SignResult.from(this.pkcs7, SignResult signResult) : super.from(signResult);

  @override
  String toString() => "${super.toString()}\nPKCS7: $pkcs7";
}
