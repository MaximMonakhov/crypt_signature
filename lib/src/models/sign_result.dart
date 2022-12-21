import 'dart:convert';
import 'dart:io';

import 'package:crypt_signature/src/models/certificate.dart';
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

  factory SignResult(Certificate certificate, {required String digest, required String signature, required String signatureAlgorithm}) {
    /// Нативные функции win32 возвращают развернутую сигнатуру
    if (Platform.isIOS) signature = reverseSignature(signature);
    return SignResult._(certificate, digest, signature, signatureAlgorithm);
  }

  SignResult._(this.certificate, this.digest, this.signature, this.signatureAlgorithm);

  @override
  String toString() =>
      "Сертификат из контейнера с приватным ключем: ${certificate.certificate.truncate()}\nDigest: ${digest.truncate()}\nSignature: ${signature.truncate()}\nАлгоритм сигнатуры: $signatureAlgorithm";

  static String reverseSignature(String signature) => base64.encode(base64.decode(signature.replaceAll("\n", "")).reversed.toList());
}
