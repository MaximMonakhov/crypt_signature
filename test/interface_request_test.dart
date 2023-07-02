// ignore_for_file: avoid_dynamic_calls

import 'dart:convert';

import 'package:crypt_signature/crypt_signature.dart';
import 'package:crypto/crypto.dart';
import 'package:flutter/services.dart';
import 'package:flutter_test/flutter_test.dart';

import 'test_data.dart';

void main() {
  const channel = MethodChannel('crypt_signature');

  group('Тестирование класса InterfaceRequest.', () {
    setUpAll(() {
      TestWidgetsFlutterBinding.ensureInitialized();

      Future<String> handler(MethodCall methodCall) async {
        Map<String, dynamic>? response;

        if (methodCall.method == 'digest') {
          expect(methodCall.arguments["certificateUUID"], isNotNull);
          expect(methodCall.arguments["password"], isNotNull);

          String message = methodCall.arguments["message"] as String;
          String digest = base64.encode(sha256.convert(utf8.encode(message)).bytes);

          response = {
            "success": true,
            "message": message,
            "digestAlgorithm": "DIGEST_ALGORITHM",
            "digest": digest,
          };
        }

        if (methodCall.method == 'sign') {
          expect(methodCall.arguments["certificateUUID"], isNotNull);
          expect(methodCall.arguments["password"], isNotNull);

          String digest = methodCall.arguments["digest"] as String;
          List<int> key = utf8.encode('KEY');
          List<int> bytes = base64.decode(digest);

          var hmacSha256 = Hmac(sha256, key);
          var signature = base64.encode(hmacSha256.convert(bytes).bytes);

          response = {
            "success": true,
            "digest": digest,
            "signatureAlgorithm": "SIGNATURE_ALGORITHM",
            "signature": signature,
          };
        }

        if (response == null) throw ArgumentError;

        return json.encode(response);
      }

      TestDefaultBinaryMessengerBinding.instance!.defaultBinaryMessenger.setMockMethodCallHandler(channel, handler);
    });

    test('MessageInterfaceRequest', () async {
      MessageInterfaceRequest interfaceRequest = MessageInterfaceRequest("MESSAGE");
      Certificate certificate = Certificate.fromBase64({"alias": TestData.kristaCertificateAlias, "certificate": TestData.kristaRawCertificate});
      SignResult signResult = await interfaceRequest.signer(certificate, "PASSWORD");
      expect(signResult.certificate, certificate);
      expect(signResult.digest, "sZTZIBjWB0I0KAxfW4hknI2xTvTyw3RtiiOJag9vO2Y=");
      expect(signResult.signature.length, 44);
      expect(signResult.signatureAlgorithm, "SIGNATURE_ALGORITHM");
    });

    test('PKCS7MessageInterfaceRequest', () async {
      PKCS7MessageInterfaceRequest interfaceRequest = PKCS7MessageInterfaceRequest((certificate) async => "MESSAGE");
      Certificate certificate = Certificate.fromBase64({"alias": TestData.kristaCertificateAlias, "certificate": TestData.kristaRawCertificate});
      SignResult signResult = await interfaceRequest.signer(certificate, "PASSWORD");
      expect(signResult.certificate, certificate);
      expect(signResult.digest.length, 44);
      expect(signResult.signature.length, 44);
      expect(signResult.signatureAlgorithm, "SIGNATURE_ALGORITHM");
      expect(signResult, isA<PKCS7SignResult>());
      signResult as PKCS7SignResult;
      expect(signResult.initialDigest, base64.encode(sha256.convert(utf8.encode("MESSAGE")).bytes));
      expect(signResult.pkcs7.certificate, certificate);
      expect(signResult.pkcs7.digest, signResult.initialDigest);
      expect(signResult.pkcs7.signature, signResult.signature);
      expect(signResult.pkcs7.signerInfo.algorithm, Algorithm.algorithms[1]);
    });

    test('PKCS7HASHInterfaceRequest', () async {
      PKCS7HASHInterfaceRequest interfaceRequest =
          PKCS7HASHInterfaceRequest((certificate) async => base64.encode(sha256.convert(utf8.encode("MESSAGE")).bytes));
      Certificate certificate = Certificate.fromBase64({"alias": TestData.kristaCertificateAlias, "certificate": TestData.kristaRawCertificate});
      SignResult signResult = await interfaceRequest.signer(certificate, "PASSWORD");
      expect(signResult.certificate, certificate);
      expect(signResult.digest.length, 44);
      expect(signResult.signature.length, 44);
      expect(signResult.signatureAlgorithm, "SIGNATURE_ALGORITHM");
      expect(signResult, isA<PKCS7SignResult>());
      signResult as PKCS7SignResult;
      expect(signResult.initialDigest, base64.encode(sha256.convert(utf8.encode("MESSAGE")).bytes));
      expect(signResult.pkcs7.certificate, certificate);
      expect(signResult.pkcs7.digest, signResult.initialDigest);
      expect(signResult.pkcs7.signature, signResult.signature);
      expect(signResult.pkcs7.signerInfo.algorithm, Algorithm.algorithms[1]);
    });

    test('CustomInterfaceRequest', () async {
      CustomInterfaceRequest interfaceRequest = CustomInterfaceRequest(
        (certificate, password) async => SignResult(
          certificate,
          digest: "DIGEST",
          signature: "SIGNATURE",
          signatureAlgorithm: "SIGNATURE_ALGORITHM",
        ),
      );
      Certificate certificate = Certificate.fromBase64({"alias": TestData.kristaCertificateAlias, "certificate": TestData.kristaRawCertificate});
      SignResult signResult = await interfaceRequest.signer(certificate, "PASSWORD");
      expect(signResult.certificate, certificate);
      expect(signResult.digest, "DIGEST");
      expect(signResult.signature, "SIGNATURE");
      expect(signResult.signatureAlgorithm, "SIGNATURE_ALGORITHM");
    });

    test('XMLInterfaceRequest', () async {
      // TODO: добавить тест для XMLInterfaceRequest
    });
  });
}
