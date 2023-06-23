import 'dart:convert';

import 'package:crypt_signature/crypt_signature.dart';
import 'package:flutter_test/flutter_test.dart';

import 'test_data.dart';

void main() {
  group("Тестирование класса PKCS7.", () {
    PKCS7 createPKCS7(String certificate) => PKCS7(
          Certificate.fromBase64({"certificate": certificate, "alias": "CERT_ALIAS"}),
          base64.encode("TEST_DIGEST".codeUnits),
          signTime: DateTime.parse("2012-02-27 13:27:00").toUtc(),
        );

    test('В base64. Сертификат Криста УЦ', () {
      expect(createPKCS7(TestData.kristaRawCertificate).content, TestData.kristaRawPKCS7);
    });

    test('Из base64. Сертификат КриптоПРО УЦ', () {
      expect(createPKCS7(TestData.cryptoProRawCertificate).content, TestData.cryptoProRawPKCS7);
    });

    test('Прикрепление сигнатуры', () {
      expect(false, TestData.cryptoProRawPKCS7 == TestData.cryptoProRawPKCS7WithSignature);
      PKCS7 pkcs7 = createPKCS7(TestData.cryptoProRawCertificate);
      expect(pkcs7.content, TestData.cryptoProRawPKCS7);
      pkcs7.attachSignature(base64.encode("TEST_SIGNATURE".codeUnits));
      expect(pkcs7.content, TestData.cryptoProRawPKCS7WithSignature);
    });
  });
}
