import 'dart:convert';

import 'package:crypt_signature/crypt_signature.dart';
import 'package:flutter_test/flutter_test.dart';

void main() {
  const String cryptoProAlias = "qwerty";
  const String cryptoProRawCertificate =
      "MIIDczCCAyKgAwIBAgITEgBgwteSYfum6FWXfAABAGDC1zAIBgYqhQMCAgMwfzEjMCEGCSqGSIb3DQEJARYUc3VwcG9ydEBjcnlwdG9wcm8ucnUxCzAJBgNVBAYTAlJVMQ8wDQYDVQQHEwZNb3Njb3cxFzAVBgNVBAoTDkNSWVBUTy1QUk8gTExDMSEwHwYDVQQDExhDUllQVE8tUFJPIFRlc3QgQ2VudGVyIDIwHhcNMjIxMjIxMTA0NzA1WhcNMjMwMzIxMTA1NzA1WjB5MRUwEwYJKoZIhvcNAQkBFgZxd2VydHkxDzANBgNVBAMMBnF3ZXJ0eTEPMA0GA1UECwwGcXdlcnR5MQ8wDQYDVQQKDAZxd2VydHkxDzANBgNVBAcMBnF3ZXJ0eTEPMA0GA1UECAwGcXdlcnR5MQswCQYDVQQGEwJSVTBmMB8GCCqFAwcBAQEBMBMGByqFAwICJAAGCCqFAwcBAQICA0MABECxGEagxV8Q5ZJQLcjI/giTAmng2EBWFF94x6TkxC6Rk/dLkyhon3ykgCh6TeugIozti4aWzS5ytWdC8rK3psobo4IBdjCCAXIwDgYDVR0PAQH/BAQDAgTwMBMGA1UdJQQMMAoGCCsGAQUFBwMCMB0GA1UdDgQWBBS+FM75aN9Ap02nltPA8Neh9xhxFjAfBgNVHSMEGDAWgBROgz4Uae/sXXqVK18R/jcyFklVKzBcBgNVHR8EVTBTMFGgT6BNhktodHRwOi8vdGVzdGNhLmNyeXB0b3Byby5ydS9DZXJ0RW5yb2xsL0NSWVBUTy1QUk8lMjBUZXN0JTIwQ2VudGVyJTIwMigxKS5jcmwwgawGCCsGAQUFBwEBBIGfMIGcMGQGCCsGAQUFBzAChlhodHRwOi8vdGVzdGNhLmNyeXB0b3Byby5ydS9DZXJ0RW5yb2xsL3Rlc3QtY2EtMjAxNF9DUllQVE8tUFJPJTIwVGVzdCUyMENlbnRlciUyMDIoMSkuY3J0MDQGCCsGAQUFBzABhihodHRwOi8vdGVzdGNhLmNyeXB0b3Byby5ydS9vY3NwL29jc3Auc3JmMAgGBiqFAwICAwNBABq7fVu9DmqjW59Jo2rlikm+U1ID2avp0Ogj+QLPc+q5nxm8TdOWidnWOsZBCRLMHqnUvS5YamaDM1LtwKJ5xAg=";
  const String kristaCertificateAlias = 'ООО "НПО "Криста" тест';
  const String kristaRawCertificate =
      "MIIFXjCCBQugAwIBAgIRATpnjQDdrny9TEADyZTTLjYwCgYIKoUDBwEBAwIwgZMxGDAWBgUqhQNkARINMDAwMDAwMDAwMDAwMDEaMBgGCCqFAwOBAwEBEgwwMDAwMDAwMDAwMDAxCzAJBgNVBAYTAlJVMQ8wDQYDVQQIDAY3NiBZYXIxEDAOBgNVBAcMB1J5Ymluc2sxCzAJBgNVBAsMAkNBMQ8wDQYDVQQKDAZrcmlzdGExDTALBgNVBAMMBHJvb3QwHhcNMjIwNzI1MDgyNDUwWhcNMjMwNzI1MDgzNDUwWjCCAckxFTATBgUqhQNkBAwKNDY4OTU3NjgxMjEbMBkGCSqGSIb3DQEJARYMdGVzdEB0ZXN0LnJ1MRYwFAYFKoUDZAMSCzIyMjIyMjIyMjIyMRgwFgYFKoUDZAESDTExMTc3NDY3NTM4NzExGzAZBgNVBAwMEtCU0L7Qu9C20L3QvtGB0YLRjDEjMCEGA1UECwwa0J/QvtC00YDQsNC30LTQtdC70LXQvdC40LUxLzAtBgNVBAoMJtCe0J7QniAi0J3Qn9CeICLQmtGA0LjRgdGC0LAiINGC0LXRgdGCMSkwJwYDVQQJDCAxLdGPINCS0YvQsdC+0YDQs9GB0LrQsNGPINC0LiA1MDEXMBUGA1UEBwwO0KDRi9Cx0LjQvdGB0LoxMTAvBgNVBAgMKDc2INCv0YDQvtGB0LvQsNCy0YHQutCw0Y8g0L7QsdC70LDRgdGC0YwxCzAJBgNVBAYTAlJVMSAwHgYDVQQqDBfQmNC80Y8g0J7RgtGH0LXRgdGC0LLQvjEXMBUGA1UEBAwO0KTQsNC80LjQu9C40Y8xLzAtBgNVBAMMJtCe0J7QniAi0J3Qn9CeICLQmtGA0LjRgdGC0LAiINGC0LXRgdGCMGYwHwYIKoUDBwEBAQEwEwYHKoUDAgIkAAYIKoUDBwEBAgIDQwAEQCc2DeOrUtOL93fZljHIIZhUMUX+xCao6RKstk2mgvGEQHEM+V0kZLnQqUeZ2VAZdIy1p1LynwOvrMkmnUybdW6jggH4MIIB9DAOBgNVHQ8BAf8EBAMCA+gwHQYDVR0OBBYEFGfRd7zixOIBtVm/OHhPrXUtMKxtMDQGCSsGAQQBgjcVBwQnMCUGHSqFAwICMgEJg934XYaqkVCE4ZU0h8qsFYOVEZI4AgEBAgEAMIGrBgNVHSUEgaMwgaAGCCsGAQUFBwMCBggrBgEFBQcDBAYJKoUDA4ICAQMWBgkqhQMDggIBAxIGCSqFAwOCAgEDFQYJKoUDA4ICAQMUBgkqhQMDggIBAxAGCSqFAwOCAgEDDgYJKoUDA4ICAQMRBgkqhQMDggIBAw8GCSqFAwOCAgEDFwYJKoUDA4ICAQMKBgkqhQMDggIBAwQGByqFAwICIgYGCCsGAQUFBwMDMAwGBSqFA2RyBAMCAQAwgdAGA1UdIwSByDCBxYAUtJH9cXDYMaFkS19rxKfhF+6BBZGhgZmkgZYwgZMxGDAWBgUqhQNkARINMDAwMDAwMDAwMDAwMDEaMBgGCCqFAwOBAwEBEgwwMDAwMDAwMDAwMDAxCzAJBgNVBAYTAlJVMQ8wDQYDVQQIDAY3NiBZYXIxEDAOBgNVBAcMB1J5Ymluc2sxCzAJBgNVBAsMAkNBMQ8wDQYDVQQKDAZrcmlzdGExDTALBgNVBAMMBHJvb3SCEQHbGB0BF65TlEhp8YwuJHx5MAoGCCqFAwcBAQMCA0EANu1jHr4uH17K+EACOrvzkiVWsBe58sthxgFKmMrMwWjjXggWtQXuZmAA/mP2jQo8gD60xUFe5GRzbPaetajWsQ==";

  group('Тестирование класса Certificate.', () {
    test('Из base64. Сертификат КриптоПРО УЦ', () {
      Certificate certificate = Certificate.fromBase64({"alias": cryptoProAlias, "certificate": cryptoProRawCertificate});

      expect(certificate.algorithm, Algorithm.findAlgorithmByPublicKeyOID("1.2.643.7.1.1.1.1"));
      expect(certificate.certificate, cryptoProRawCertificate);
      expect(certificate.notAfterDate, "10:57 21-03-2023");
      expect(certificate.serialNumber, "120060c2d79261fba6e855977c00010060c2d7");
      expect(certificate.subjectDN.contains("email"), true);
    });

    test('Из base64. Сертификат Криста УЦ', () {
      Certificate certificate = Certificate.fromBase64({"alias": kristaCertificateAlias, "certificate": kristaRawCertificate});

      expect(certificate.algorithm, Algorithm.findAlgorithmByPublicKeyOID("1.2.643.7.1.1.1.1"));
      expect(certificate.certificate, kristaRawCertificate);
      expect(certificate.notAfterDate, "08:34 25-07-2023");
      expect(certificate.serialNumber, "013a678d00ddae7cbd4c4003c994d32e36");
      expect(certificate.subjectDN.contains("Рыбинск"), true);
      expect(certificate.subjectDN.contains("22222222222"), true);
    });

    test('Из/в JSON', () {
      Certificate kristaCertificate = Certificate.fromBase64({"alias": kristaCertificateAlias, "certificate": kristaRawCertificate});
      Certificate cryptoProCertificate = Certificate.fromBase64({"alias": cryptoProAlias, "certificate": cryptoProRawCertificate});

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
