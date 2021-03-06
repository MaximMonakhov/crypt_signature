import 'dart:async';
import 'dart:io';

import 'package:crypt_signature/ui/home.dart';
import 'package:crypt_signature/utils/fade_in_page_transition.dart';
import 'package:flutter/material.dart';
import 'package:path_provider/path_provider.dart';
import 'package:shared_preferences/shared_preferences.dart';

import 'bloc/native.dart';

class CryptSignature {
  static SharedPreferences sharedPreferences;
  static BuildContext rootContext;
  String data;

  /// Подписать данные
  static Future<String> signData(BuildContext context, String base64Data,
      {String title = "Подпись", String hint = "Выберите сертификат"}) async {
    Native.data = base64Data;
    CryptSignature.rootContext = context;

    sharedPreferences = await SharedPreferences.getInstance();

    Directory directory = await getApplicationDocumentsDirectory();
    await Directory(directory.path + '/certificates').create();

    String result = await Navigator.of(context).push(
        FadePageRoute(builder: (context) => Home(title: title, hint: hint)));

    return result;
  }

  /// Подписать отложенные данные
  static Future<String> sign(BuildContext context,
      Future<String> Function(String rawCertificate) onCertificateSelected,
      {String title = "Подпись", String hint = "Выберите сертификат"}) async {
    CryptSignature.rootContext = context;

    sharedPreferences = await SharedPreferences.getInstance();

    Directory directory = await getApplicationDocumentsDirectory();
    await Directory(directory.path + '/certificates').create();

    String result = await Navigator.of(context).push(FadePageRoute(
        builder: (context) => Home(
              title: title,
              hint: hint,
              onCertificateSelected: onCertificateSelected,
            )));

    return result;
  }

  static void clear() {
    CryptSignature.sharedPreferences.clear();
  }
}
