import 'dart:convert';

import 'package:crypt_signature/crypt_signature.dart';
import 'package:flutter_test/flutter_test.dart';

import 'utils/test_data.dart';

void main() {
  group("Тестирование класса PKCS7.", () {
    PKCS7 createPKCS7(String certificate, {String? signature, String? message}) => PKCS7(
          Certificate.fromBase64({"certificate": certificate, "alias": "CERT_ALIAS"}),
          base64.encode(utf8.encode("DIGEST")),
          base64.encode(utf8.encode("CERTIFICATE_DIGEST")),
          signTime: DateTime.utc(1986),
          signature: signature,
          message: message,
        );

    test('В base64. Сертификат Криста УЦ', () {
      expect(createPKCS7(TestData.kristaRawCertificate).encoded, TestData.kristaRawPKCS7);
    });

    test('Из base64. Сертификат КриптоПРО УЦ', () {
      expect(createPKCS7(TestData.cryptoProRawCertificate).encoded, TestData.cryptoProRawPKCS7);
    });

    test('Прикрепление сигнатуры', () {
      expect(false, TestData.kristaRawPKCS7 == TestData.kristaRawPKCS7WithSignature);
      PKCS7 pkcs7 = createPKCS7(TestData.kristaRawCertificate);
      //int length = pkcs7.root.totalEncodedByteLength.encodedBytes.length;
      pkcs7.signerInfo.attachSignature(base64.encode(utf8.encode("SIGNATURE")));
      expect(pkcs7.encoded, TestData.kristaRawPKCS7WithSignature);
      //expect(pkcs7.root.encodedBytes.length, greaterThan(length));
    });

    test('Прикрепление сигнатуры повторно', () {
      PKCS7 pkcs7_1 = createPKCS7(TestData.kristaRawCertificate)..signerInfo.attachSignature(base64.encode("TEST_SIGNATURE".codeUnits));
      PKCS7 pkcs7_2 = createPKCS7(TestData.kristaRawCertificate, signature: base64.encode("TEST_SIGNATURE".codeUnits));

      expect(pkcs7_1.signerInfo.signature, isNotNull);
      expect(pkcs7_2.signerInfo.signature, isNotNull);
      expect(pkcs7_1.signerInfo.signature, isNotNull);
      expect(pkcs7_2.signerInfo.signature, isNotNull);
      expect(() => pkcs7_1.signerInfo.attachSignature(base64.encode("TEST_SIGNATURE".codeUnits)), throwsException);
      expect(() => pkcs7_2.signerInfo.attachSignature(base64.encode("TEST_SIGNATURE".codeUnits)), throwsException);
    });

    test('Прикрепленная подпись', () {
      PKCS7 pkcs7 = createPKCS7(TestData.kristaRawCertificate, message: "VEVTVF9NRVNTQUdFXzEyMw==");
      String rawPKCS7 = pkcs7.encoded;
      expect(rawPKCS7, TestData.kristaRawPKCS7Attached);
      expect(pkcs7.toString().contains("TEST_MESSAGE_123"), true);
    });
  });
}
