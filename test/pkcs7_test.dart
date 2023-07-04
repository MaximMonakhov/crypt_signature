import 'dart:convert';

import 'package:crypt_signature/crypt_signature.dart';
import 'package:flutter_test/flutter_test.dart';

import 'test_data.dart';

void main() {
  group("Тестирование класса PKCS7.", () {
    PKCS7 createPKCS7(String certificate) => PKCS7(
          Certificate.fromBase64({"certificate": certificate, "alias": "CERT_ALIAS"}),
          base64.encode(utf8.encode("DIGEST")),
          base64.encode(utf8.encode("CERTIFICATE_DIGEST")),
          signTime: DateTime.parse("2012-02-27 13:27:00").toUtc(),
        );

    test('В base64. Сертификат Криста УЦ', () {
      expect(createPKCS7(TestData.kristaRawCertificate).encoded, TestData.kristaRawPKCS7);
    });

    test('Из base64. Сертификат КриптоПРО УЦ', () {
      expect(createPKCS7(TestData.cryptoProRawCertificate).encoded, TestData.cryptoProRawPKCS7);
    });

    test('Прикрепление сигнатуры', () {
      expect(false, TestData.cryptoProRawPKCS7 == TestData.kristaRawPKCS7WithSignature);
      PKCS7 pkcs7 = createPKCS7(TestData.kristaRawCertificate);
      pkcs7.signerInfo.attachSignature(base64.encode(utf8.encode("SIGNATURE")));
      expect(pkcs7.encoded, TestData.kristaRawPKCS7WithSignature);
    });
  });
}
