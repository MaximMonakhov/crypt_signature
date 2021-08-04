import 'dart:convert';
import 'dart:io';

import 'package:api_event/models/api_response.dart';
import 'package:crypt_signature/models/certificate.dart';
import 'package:flutter/services.dart';
import 'package:path_provider/path_provider.dart';

class Native {
  static const MethodChannel _channel = const MethodChannel('crypt_signature');
  static String data;

  static Future<bool> initCSP() async {
    try {
      dynamic result = await _channel.invokeMethod("initCSP");
      return result;
    } catch (exception) {
      print("Не удалось инициализировать провайдер: " + exception.toString());
      return false;
    }
  }

  static Future<ApiResponse<Certificate>> installCertificate(
      File file, String password) async {
    try {
      String certificateInfo = await _channel.invokeMethod("installCertificate",
          {"pathToCert": file.path, "password": password});

      Certificate certificate =
          Certificate.fromJson(json.decode(certificateInfo));

      Directory directory = await getApplicationDocumentsDirectory();
      String filePath =
          directory.path + "/certificates/" + certificate.uuid + ".pfx";

      File(filePath);
      await file.copy(filePath);

      file.delete();

      return ApiResponse.completed(data: certificate);
    } catch (exception) {
      return ApiResponse.error(message: exception.toString());
    }
  }

  static Future<ApiResponse<String>> sign(
      Certificate certificate, String password) async {
    try {
      String result = await _channel.invokeMethod("sign",
          {"uuid": certificate.uuid, "password": password, "data": data});

      return ApiResponse.completed(data: result);
    } catch (exception) {
      return ApiResponse.error(message: exception.toString());
    }
  }
}
