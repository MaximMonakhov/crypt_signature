import 'dart:async';
import 'dart:io';

import 'package:crypt_signature/src/inherited_crypt_signature.dart';
import 'package:crypt_signature/src/models/certificate.dart';
import 'package:crypt_signature/src/models/digest_result.dart';
import 'package:crypt_signature/src/models/interface_request.dart';
import 'package:crypt_signature/src/models/license.dart';
import 'package:crypt_signature/src/models/sign_result.dart';
import 'package:crypt_signature/src/native/native.dart';
import 'package:crypt_signature/src/ui/home_widget.dart';
import 'package:crypt_signature/src/utils/fade_in_page_transition.dart';
import 'package:flutter/material.dart';
import 'package:path_provider/path_provider.dart';
import 'package:shared_preferences/shared_preferences.dart';

class CryptSignature {
  static SharedPreferences? sharedPreferences;

  /// Открыть экран выбора сертификата и подписать
  /// В случает подписи PKCS7 на Android возвращает [PKCS7SignResult]
  /// В случает подписи XML возвращает [XMLDSIGSignResult]
  /// Возвращает [SignResult] для всеъ остальных
  static Future<T?> interface<T extends SignResult>(
    BuildContext context,
    InterfaceRequest<T> interfaceRequest, {
    String title = "Подпись",
    String hint = "Выберите сертификат",
  }) async {
    NavigatorState navigator = Navigator.of(context);
    sharedPreferences = await SharedPreferences.getInstance();
    Directory directory = await getApplicationDocumentsDirectory();
    await Directory('${directory.path}/certificates').create();

    T? result = await navigator.push(
      FadePageRoute(
        builder: (context) => InheritedCryptSignature(
          interfaceRequest,
          context,
          child: HomeWidget(title: title, hint: hint),
        ),
      ),
    );

    return result;
  }

  /// Инициализировать криптопровайдер
  static Future<bool> initCSP() => Native.initCSP();

  /// Установить новую лицензию
  static Future<License> setLicense(String license) => Native.setLicense(license);

  /// Получить информацию о текущей лицензии
  static Future<License> getLicense() => Native.getLicense();

  /// Добавить сертификат в хранилище
  static Future<Certificate> addCertificate(File file, String password) => Native.addCertificate(file, password);

  /// Вычислить хэш сообщения/документа
  static Future<DigestResult> digest(Certificate certificate, String password, String message) => Native.digest(certificate, password, message);

  /// Вычислить подпись хэша
  static Future<SignResult> sign(Certificate certificate, String password, String digest) => Native.sign(certificate, password, digest);

  // /// Создать [PKCS7] и атрибуты подписи на основе [digest]
  // static Future<PKCS7> createPKCS7(Certificate certificate, String password, String digest) => Native.createPKCS7(certificate, password, digest);

  // /// Прикрепить к [pkcs7] сигнатуру [signature]
  // static Future<PKCS7> addSignatureToPKCS7(PKCS7 pkcs7, String signature) => Native.addSignatureToPKCS7(pkcs7, signature);

  /// Получить список сертификатов, добавленных пользователем
  static Future<List<Certificate>> getCertificates() async {
    sharedPreferences ??= await SharedPreferences.getInstance();
    return Certificate.storage.get();
  }

  /// Очистить список сертификатов
  static Future<bool> clear() async {
    Directory applicationDirectory = await getApplicationDocumentsDirectory();
    Directory directory = Directory('${applicationDirectory.path}/certificates');

    if (directory.existsSync()) await directory.delete(recursive: true);
    sharedPreferences ??= await SharedPreferences.getInstance();
    return sharedPreferences!.remove("Certificate");
  }
}
