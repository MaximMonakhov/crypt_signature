import 'package:crypt_signature/crypt_signature.dart';
import 'package:flutter_test/flutter_test.dart';

import 'test_data.dart';

void main() {
  group("Тестирование класса PKCS7.", () {
    PKCS7 createPKCS7(String certificate) => PKCS7(
          Certificate.fromBase64({"certificate": certificate, "alias": "CERT_ALIAS"}),
          "77b7fa410c9ac58a25f49bca7d0468c9296529315eaca76bd1a10f376d1f4294",
          "77b7fa410c9ac58a25f49bca7d0468c9296529315eaca76bd1a10f376d1f",
          signTime: DateTime.parse("2012-02-27 13:27:00").toUtc(),
        );

    test('В base64. Сертификат Криста УЦ', () {
      expect(createPKCS7(TestData.kristaRawCertificate).content, TestData.kristaRawPKCS7);
    });

    test('Из base64. Сертификат КриптоПРО УЦ', () {
      expect(createPKCS7(TestData.cryptoProRawCertificate).content, TestData.cryptoProRawPKCS7);
    });

    test('Прикрепление сигнатуры', () {
      expect(false, TestData.cryptoProRawPKCS7 == TestData.kristaRawPKCS7WithSignature);
      PKCS7 pkcs7 = createPKCS7(TestData.kristaRawCertificate);
      expect(pkcs7.content, TestData.kristaRawPKCS7);
      pkcs7.attachSignature("gFayPzG/MSdgzGL5vBmoiRHXe2FOBc7+DTl06DkYza/KY0TfK96oSSw6Lia5WGKfynw9ZIYBnw0IFi+I1Pj7ug==");
      expect(pkcs7.content, TestData.kristaRawPKCS7WithSignature);
    });
  });
}
