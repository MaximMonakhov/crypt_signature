import 'dart:convert';
import 'dart:io';

import 'certificate.dart';

/// Результат подписи
class SignResult {
  /// Сертификат из контейнера с приватным ключем
  final Certificate certificate;

  /// Подписываемые данные
  final String data;

  /// Сигнатура
  final String signature;

  factory SignResult(Certificate certificate, String data, String signature) {
    /// Нативные функции win32 возвращают развернутую сигнатуру
    if (Platform.isIOS) signature = reverseSignature(signature);
    return SignResult._(certificate, data, signature);
  }

  SignResult._(this.certificate, this.data, this.signature);

  static String reverseSignature(String signature) =>
      base64.encode(base64.decode(signature.replaceAll("\n", "")).reversed.toList());
}
