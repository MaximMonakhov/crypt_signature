import 'dart:convert';

import 'package:crypt_signature/crypt_signature.dart';
import 'package:flutter_test/flutter_test.dart';

import 'test_data.dart';

void main() {
  group('Тестирование класса Certificate.', () {
    test('Из base64. Сертификат КриптоПРО УЦ', () {
      Certificate certificate = Certificate.fromBase64({"alias": TestData.cryptoProAlias, "certificate": TestData.cryptoProRawCertificate});

      expect(certificate.algorithm, Algorithm.findAlgorithmByPublicKeyOID("1.2.643.7.1.1.1.1"));
      expect(certificate.certificate, TestData.cryptoProRawCertificate);
      expect(certificate.notAfterDate, "10:57 21-03-2023");
      expect(certificate.serialNumber, "120060c2d79261fba6e855977c00010060c2d7");
      expect(certificate.subjectDN.contains("email"), true);
      expect(base64.encode(utf8.encode(json.encode(certificate.parameterMap))), TestData.cryptoProParameters);
      expect(base64.encode(utf8.encode(certificate.certificateDescription)), TestData.cryptoProDescription);
    });

    test('Из base64. Сертификат Криста УЦ', () {
      Certificate certificate = Certificate.fromBase64({"alias": TestData.kristaCertificateAlias, "certificate": TestData.kristaRawCertificate});

      expect(certificate.algorithm, Algorithm.findAlgorithmByPublicKeyOID("1.2.643.7.1.1.1.1"));
      expect(certificate.certificate, TestData.kristaRawCertificate);
      expect(certificate.notAfterDate, "08:34 25-07-2023");
      expect(certificate.serialNumber, "013a678d00ddae7cbd4c4003c994d32e36");
      expect(certificate.subjectDN.contains("Рыбинск"), true);
      expect(certificate.subjectDN.contains("22222222222"), true);
      expect(base64.encode(utf8.encode(json.encode(certificate.parameterMap))), TestData.kristaParameters);
      expect(base64.encode(utf8.encode(certificate.certificateDescription)), TestData.kristaDescription);
    });

    test('Из/в JSON', () {
      Certificate kristaCertificate = Certificate.fromBase64({"alias": TestData.kristaCertificateAlias, "certificate": TestData.kristaRawCertificate});
      Certificate cryptoProCertificate = Certificate.fromBase64({"alias": TestData.cryptoProAlias, "certificate": TestData.cryptoProRawCertificate});

      String kristaJSON = json.encode(kristaCertificate.toJson());
      String cryptoProJSON = json.encode(cryptoProCertificate.toJson());

      Certificate kristaCertificateFromJSON = Certificate.fromJson(json.decode(kristaJSON) as Map<String, dynamic>);
      Certificate cryptoPROCertificateFromJSON = Certificate.fromJson(json.decode(cryptoProJSON) as Map<String, dynamic>);

      expect(kristaCertificate, kristaCertificateFromJSON);
      expect(cryptoProCertificate, cryptoPROCertificateFromJSON);
      expect(kristaJSON, json.encode(kristaCertificateFromJSON.toJson()));
      expect(cryptoProJSON, json.encode(cryptoPROCertificateFromJSON.toJson()));
    });

    test('Добавление ведущих нулей при преобразовании серийного номера в hex', () {
      String serialNumber1 = Certificate.parseSerialNumberToHex(BigInt.parse("548226392223302168094978710813409480160"));
      String serialNumber2 = Certificate.parseSerialNumberToHex(BigInt.parse("162531608789284853759428856571333747351"));
      String serialNumber3 = Certificate.parseSerialNumberToHex(BigInt.parse("7128820800948151058522410848446416797"));
      String serialNumber4 = Certificate.parseSerialNumberToHex(BigInt.parse("1132170373875453231367375"));

      expect(serialNumber1, "019c70900090af7ebc42a6d54638d30de0");
      expect(serialNumber2, "7a46730095adb3bb4fd76b47428ca297");
      expect(serialNumber3, "055cf6007bad0e9541c76d62897d879d");
      expect(serialNumber4, "00efbf14360000000004cf");
    });
  });
}
