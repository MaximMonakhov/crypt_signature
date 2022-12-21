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

  /// PKCS7
  PKCS7? pkcs7;

  factory SignResult(Certificate certificate, {required String digest, required String signature, required String signatureAlgorithm, PKCS7? pkcs7}) {
    /// Нативные функции win32 возвращают развернутую сигнатуру
    if (Platform.isIOS) signature = reverseSignature(signature);
    return SignResult._(certificate, digest, signature, signatureAlgorithm, pkcs7);
  }

  SignResult._(this.certificate, this.digest, this.signature, this.signatureAlgorithm, this.pkcs7);

  @override
  String toString() =>
      "Сертификат из контейнера с приватным ключем: ${certificate.certificate.truncate()}\nDigest: ${digest.truncate()}\nSignature: ${signature.truncate()}\nАлгоритм сигнатуры: $signatureAlgorithm";

  static String reverseSignature(String signature) => base64.encode(base64.decode(signature.replaceAll("\n", "")).reversed.toList());
}
