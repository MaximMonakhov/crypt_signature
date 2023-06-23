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

  static Future<bool> initCSP() async {
    try {
      bool? response = await _channel.invokeMethod<bool>("initCSP");
      if (response!) return true;
      throw ApiResponseException("Не удалось инициализировать провайдер", "Неизвестная ошибка");
    } on ApiResponseException {
      rethrow;
    } on PlatformException catch (exception) {
      throw ApiResponseException(exception.message, exception.details.toString());
    } on Exception catch (exception) {
      throw ApiResponseException("Ошибка при инициализации провайдера", exception.toString());
    }
  }

  static Future<Certificate> addCertificate(File file, String password) async {
    try {
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
    } on ApiResponseException {
      rethrow;
    } on PlatformException catch (exception) {
      throw ApiResponseException(exception.message, exception.details.toString());
    } on Exception catch (exception) {
      throw ApiResponseException("Не удалось добавить сертификат в хранилище", exception.toString());
    }
  }

  static Future<License> setLicense(String licenseSerialNumber) async {
    try {
      String? response = await _channel.invokeMethod("setLicense", {"license": licenseSerialNumber});
      Map<String, dynamic> map = json.decode(response!) as Map<String, dynamic>;
      License license = License.fromMap(map);
      return license;
    } on PlatformException catch (exception) {
      throw ApiResponseException(exception.message, exception.details.toString());
    } on Exception catch (exception) {
      throw ApiResponseException("Не удалось установить лицензию", exception.toString());
    }
  }

  static Future<License> getLicense() async {
    try {
      String? response = await _channel.invokeMethod("getLicense");
      Map<String, dynamic> map = json.decode(response!) as Map<String, dynamic>;
      License license = License.fromMap(map);
      return license;
    } on PlatformException catch (exception) {
      throw ApiResponseException(exception.message, exception.details.toString());
    } on Exception catch (exception) {
      throw ApiResponseException("Не удалось получить информацию о лицензию", exception.toString());
    }
  }

  static Future<DigestResult> digest(Certificate certificate, String password, String message) async {
    try {
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
    } on PlatformException catch (exception) {
      throw ApiResponseException(exception.message, exception.details.toString());
    } on Exception catch (exception) {
      throw ApiResponseException("Не удалось получить Digest", exception.toString());
    }
  }

  static Future<SignResult> sign(Certificate certificate, String password, String digest) async {
    try {
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
    } on PlatformException catch (exception) {
      throw ApiResponseException(exception.message, exception.details.toString());
    } on Exception catch (exception) {
      throw ApiResponseException("Не удалось выполнить подпись", exception.toString());
    }
  }

  static Future<PKCS7> createPKCS7(Certificate certificate, String password, String digest) async {
    try {
      String? response = await _channel.invokeMethod("createPKCS7", {"certificateUUID": certificate.storageID, "password": password, "digest": digest});
      Map<String, dynamic> map = json.decode(response!) as Map<String, dynamic>;
      if (map["success"] as bool) return PKCS7(content: map["pkcs7"] as String, signedAttributes: map["signedAttributes"] as String);
      throw ApiResponseException(map["message"] as String?, map["exception"].toString());
    } on PlatformException catch (exception) {
      throw ApiResponseException(exception.message, exception.details.toString());
    } on Exception catch (exception) {
      throw ApiResponseException("Не удалось создать PKCS7", exception.toString());
    }
  }

  static Future<PKCS7> addSignatureToPKCS7(PKCS7 pkcs7, String signature) async {
    try {
      String? response = await _channel.invokeMethod("addSignatureToPKCS7", {"pkcs7": pkcs7.content, "signature": signature});
      Map<String, dynamic> map = json.decode(response!) as Map<String, dynamic>;
      if (map["success"] as bool) return PKCS7(content: map["pkcs7"] as String, signedAttributes: "");
      throw ApiResponseException(map["message"] as String?, map["exception"].toString());
    } on PlatformException catch (exception) {
      throw ApiResponseException(exception.message, exception.details.toString());
    } on Exception catch (exception) {
      throw ApiResponseException("Не удалось добавить сигнатуру к PKCS7", exception.toString());
    }
  }
}
