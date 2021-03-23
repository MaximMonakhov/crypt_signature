import 'dart:async';
import 'dart:convert';
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

  static Future<String> sign(BuildContext context, String base64Data,
      {String title = "Подпись", String hint = "Выберите сертификат"}) async {
    Native.data = base64Data;
    CryptSignature.rootContext = context;

    sharedPreferences = await SharedPreferences.getInstance();
    //await sharedPreferences.clear();

    Directory directory = await getApplicationDocumentsDirectory();
    await Directory(directory.path + '/certificates').create();

    String result = await Navigator.of(context).push(
        FadePageRoute(builder: (context) => Home(title: title, hint: hint)));

    return result;
  }
}
