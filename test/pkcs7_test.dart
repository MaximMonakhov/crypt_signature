import 'dart:convert';

import 'package:crypt_signature/crypt_signature.dart';
import 'package:flutter_test/flutter_test.dart';

import 'test_data.dart';

void main() {
  group("Тестирование класса PKCS7.", () {
    PKCS7 createPKCS7(String certificate, {String? signature}) => PKCS7(
          Certificate.fromBase64({"certificate": certificate, "alias": "CERT_ALIAS"}),
          base64.encode("TEST_DIGEST".codeUnits),
          signTime: DateTime.parse("2012-02-27 13:27:00").toUtc(),
          signature: signature,
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
      int length = pkcs7.root.encodedBytes.length;
      expect(pkcs7.content, TestData.cryptoProRawPKCS7);
      pkcs7.attachSignature(base64.encode("TEST_SIGNATURE".codeUnits));
      expect(pkcs7.content, TestData.cryptoProRawPKCS7WithSignature);
      expect(pkcs7.root.encodedBytes.length, greaterThan(length));
    });

    test('Прикрепление сигнатуры повторно', () {
      PKCS7 pkcs7_1 = createPKCS7(TestData.kristaRawCertificate)..attachSignature(base64.encode("TEST_SIGNATURE".codeUnits));
      PKCS7 pkcs7_2 = createPKCS7(TestData.kristaRawCertificate, signature: base64.encode("TEST_SIGNATURE".codeUnits));

      expect(pkcs7_1.signature, isNotNull);
      expect(pkcs7_2.signature, isNotNull);
      expect(pkcs7_1.signerInfo.signature, isNotNull);
      expect(pkcs7_2.signerInfo.signature, isNotNull);
      expect(() => pkcs7_1.attachSignature(base64.encode("TEST_SIGNATURE".codeUnits)), throwsException);
      expect(() => pkcs7_2.attachSignature(base64.encode("TEST_SIGNATURE".codeUnits)), throwsException);
    });
  });
}
