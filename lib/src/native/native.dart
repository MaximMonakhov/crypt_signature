// ignore_for_file: require_trailing_commas

import 'dart:async';
import 'dart:convert';
import 'dart:io';

import 'package:crypt_signature/src/exceptions/api_response_exception.dart';
import 'package:crypt_signature/src/models/certificate.dart';
import 'package:crypt_signature/src/models/digest_result.dart';
import 'package:crypt_signature/src/models/license.dart';
import 'package:crypt_signature/src/models/pkcs7.dart';
import 'package:crypt_signature/src/models/sign_result.dart';
import 'package:flutter/services.dart';
import 'package:path_provider/path_provider.dart';

class Native {
  static const MethodChannel _channel = MethodChannel('crypt_signature');

  static Future<bool> initCSP() => _invokeWithExceptionHandler(() async {
        bool? response = await _channel.invokeMethod<bool>("initCSP");
        if (response!) return true;
        throw ApiResponseException("Не удалось инициализировать провайдер", "Неизвестная ошибка");
      }(), "Ошибка при инициализации провайдера");

  static Future<Certificate> addCertificate(File file, String password) => _invokeWithExceptionHandler(() async {
        String? response = await _channel.invokeMethod("addCertificate", {"path": file.path, "password": password});
        Map<String, dynamic> map = json.decode(response!) as Map<String, dynamic>;
        if (map["success"] as bool) {
          Certificate certificate = Certificate.fromBase64(map);
          Directory directory = await getApplicationDocumentsDirectory();
          String filePath = "${directory.path}/certificates/${certificate.uuid}.pfx";
          File(filePath);
          await file.copy(filePath);
          file.delete();
          return certificate;
        }
        throw ApiResponseException(map["message"] as String?, map["exception"].toString());
      }(), "Не удалось добавить сертификат в хранилище");

  static Future<License> setLicense(String licenseSerialNumber) => _invokeWithExceptionHandler(() async {
        String? response = await _channel.invokeMethod("setLicense", {"license": licenseSerialNumber});
        Map<String, dynamic> map = json.decode(response!) as Map<String, dynamic>;
        License license = License.fromMap(map);
        return license;
      }(), "Не удалось установить лицензию");

  static Future<License> getLicense() => _invokeWithExceptionHandler(() async {
        String? response = await _channel.invokeMethod("getLicense");
        Map<String, dynamic> map = json.decode(response!) as Map<String, dynamic>;
        License license = License.fromMap(map);
        return license;
      }(), "Не удалось получить информацию о лицензию");

  static Future<DigestResult> digest(Certificate certificate, String password, String message) => _invokeWithExceptionHandler(() async {
        String? response = await _channel.invokeMethod("digest", {"certificateUUID": certificate.storageID, "password": password, "message": message});
        Map<String, dynamic> map = json.decode(response!) as Map<String, dynamic>;
        if (map["success"] as bool) {
          return DigestResult(
            certificate: certificate,
            message: map["message"] as String,
            digestAlgorithm: map["digestAlgorithm"] as String,
            digest: (map["digest"] as String).replaceAll("\n", ""),
          );
        }
        throw ApiResponseException(map["message"] as String?, map["exception"].toString());
      }(), "Не удалось получить Digest");

  static Future<SignResult> sign(Certificate certificate, String password, String digest) => _invokeWithExceptionHandler(() async {
        String? response = await _channel.invokeMethod("sign", {"certificateUUID": certificate.storageID, "password": password, "digest": digest});
        Map<String, dynamic> map = json.decode(response!) as Map<String, dynamic>;
        if (map["success"] as bool) {
          return SignResult(
            certificate,
            digest: map["digest"] as String,
            signatureAlgorithm: map["signatureAlgorithm"] as String,
            signature: map["signature"] as String,
          );
        }
        throw ApiResponseException(map["message"] as String?, map["exception"].toString());
      }(), "Не удалось выполнить подпись");

  static Future<PKCS7> createPKCS7(Certificate certificate, String password, String digest) => _invokeWithExceptionHandler(() async {
        String? response = await _channel.invokeMethod("createPKCS7", {"certificateUUID": certificate.storageID, "password": password, "digest": digest});
        Map<String, dynamic> map = json.decode(response!) as Map<String, dynamic>;
        if (map["success"] as bool) return PKCS7(content: map["pkcs7"] as String, signedAttributes: map["signedAttributes"] as String);
        throw ApiResponseException(map["message"] as String?, map["exception"].toString());
      }(), "Не удалось создать PKCS7");

  static Future<PKCS7> addSignatureToPKCS7(PKCS7 pkcs7, String signature) => _invokeWithExceptionHandler(() async {
        String? response = await _channel.invokeMethod("addSignatureToPKCS7", {"pkcs7": pkcs7.content, "signature": signature});
        Map<String, dynamic> map = json.decode(response!) as Map<String, dynamic>;
        if (map["success"] as bool) return PKCS7(content: map["pkcs7"] as String, signedAttributes: "");
        throw ApiResponseException(map["message"] as String?, map["exception"].toString());
      }(), "Не удалось добавить сигнатуру к PKCS7");
}

Future<T> _invokeWithExceptionHandler<T>(Future<T> future, String errorMessage) async {
  try {
    return await future;
  } on ApiResponseException {
    rethrow;
  } on PlatformException catch (exception) {
    throw ApiResponseException(exception.message, exception.details.toString());
  } on Exception catch (exception) {
    throw ApiResponseException(errorMessage, exception.toString());
  }
}
