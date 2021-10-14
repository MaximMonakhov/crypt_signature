import 'dart:async';
import 'dart:io';

import 'package:crypt_signature/ui/home.dart';
import 'package:crypt_signature/utils/fade_in_page_transition.dart';
import 'package:flutter/material.dart';
import 'package:path_provider/path_provider.dart';
import 'package:shared_preferences/shared_preferences.dart';

import 'bloc/native.dart';
import 'models/certificate.dart';
import 'models/sign_result.dart';

class CryptSignature {
  static SharedPreferences sharedPreferences;
  static BuildContext rootContext;

  /// Подписать данные
  /// Возможны два сценария работы метода:
  /// 
  /// * Если данные известны сразу. 
  ///   Требуется передать данные в формате Base64 в параметр [data] для подписи
  /// 
  /// * Если для формирования данных нужен сертификат пользователя. 
  ///   Требуется передать сallback [onCertificateSelected], который отдает вам сертификат, 
  ///   выбранный пользователем, и ожидает данные в формате Base64 для подписи
  static Future<SignResult> sign(BuildContext context,
      {String data,
      Future<String> Function(Certificate certificate) onCertificateSelected,
      String title = "Подпись",
      String hint = "Выберите сертификат"}) async {
    Native.data = data;
    CryptSignature.rootContext = context;

    sharedPreferences = await SharedPreferences.getInstance();

    Directory directory = await getApplicationDocumentsDirectory();
    await Directory(directory.path + '/certificates').create();

    SignResult signResult = await Navigator.of(context).push(FadePageRoute(
        builder: (context) => Home(
              title: title,
              hint: hint,
              onCertificateSelected: onCertificateSelected,
            )));

    return signResult;
  }

  static Future clear() async {
    if (CryptSignature.sharedPreferences != null)
      await CryptSignature.sharedPreferences.clear();
  }
}
