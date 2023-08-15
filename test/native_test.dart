// ignore_for_file: avoid_dynamic_calls

import 'dart:convert';

import 'package:crypt_signature/crypt_signature.dart';
import 'package:crypt_signature/src/native/native.dart';
import 'package:file/file.dart';
import 'package:file/memory.dart';
import 'package:flutter/foundation.dart';
import 'package:flutter/services.dart';
import 'package:flutter_test/flutter_test.dart';

import 'utils/test_data.dart';

void main() {
  const channel = MethodChannel('crypt_signature');
  late Certificate certificate;

  group("Тестирование класса Native.", () {
    setUpAll(() {
      TestWidgetsFlutterBinding.ensureInitialized();

      certificate = Certificate.fromBase64({"alias": TestData.kristaCertificateAlias, "certificate": TestData.kristaRawCertificate});

      Future<String> handler(MethodCall methodCall) async {
        Map<String, dynamic>? response;

        if (methodCall.method == 'addCertificate') {
          expect(methodCall.arguments["path"], "cert.pfx");
          expect(methodCall.arguments["password"], "PASSWORD");

          response = {
            "success": true,
            "certificate": certificate.certificate,
            "alias": certificate.alias,
          };
        }

        if (methodCall.method == 'sign') {
          response = {
            "success": true,
            "digest": "DIGEST",
            "signature": "dGVzdA==",
            "signatureAlgorithm": "ALG",
          };
        }

        if (response == null) throw ArgumentError;

        return json.encode(response);
      }

      TestDefaultBinaryMessengerBinding.instance!.defaultBinaryMessenger.setMockMethodCallHandler(channel, handler);
    });

    test('Добавление сертификата', () async {
      const MethodChannel pathChannel = MethodChannel('plugins.flutter.io/path_provider');
      pathChannel.setMockMethodCallHandler((MethodCall methodCall) async => "");

      FileSystem fileSystem = MemoryFileSystem();
      fileSystem.directory('/certificates').createSync();

      File file = fileSystem.file("cert.pfx");
      file.createSync();
      file.writeAsBytesSync(base64.decode(certificate.certificate));

      Certificate response = await Native.addCertificate(file, "PASSWORD", fileSystem: fileSystem);

      expect(response, certificate);
      File createdFile = fileSystem.file("/certificates/${response.uuid}.pfx");
      expect(file.existsSync(), false);
      expect(createdFile.existsSync(), true);
      expect(createdFile.readAsBytesSync(), base64.decode(certificate.certificate));
    });

    test("Нативные функции win32 возвращают развернутую сигнатуру. Ее следует обязательно перевернуть", () async {
      debugDefaultTargetPlatformOverride = TargetPlatform.iOS;
      SignResult result = await Native.sign(certificate, "", "");
      expect(result.signature, base64.encode(base64.decode("dGVzdA==").reversed.toList()));
      debugDefaultTargetPlatformOverride = TargetPlatform.android;
      result = await Native.sign(certificate, "", "");
      expect(result.signature, "dGVzdA==");
    });
  });
}
