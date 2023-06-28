import 'dart:async';
import 'dart:io';

import 'package:crypt_signature/src/models/certificate.dart';
import 'package:crypt_signature/src/models/digest_result.dart';
import 'package:crypt_signature/src/models/interface_request.dart';
import 'package:crypt_signature/src/models/license.dart';
import 'package:crypt_signature/src/models/pkcs7.dart';
import 'package:crypt_signature/src/models/sign_result.dart';
import 'package:crypt_signature/src/native/native.dart';
import 'package:crypt_signature/src/providers/crypt_signature_provider.dart';
import 'package:crypt_signature/src/repositories/certificate_repository.dart';
import 'package:crypt_signature/src/services/license_service.dart';
import 'package:crypt_signature/src/services/lock_service.dart';
import 'package:crypt_signature/src/ui/home_widget.dart';
import 'package:crypt_signature/src/utils/crypt_signature_theme.dart';
import 'package:crypt_signature/src/utils/fade_in_page_transition.dart';
import 'package:flutter/material.dart';
import 'package:path_provider/path_provider.dart';
import 'package:provider/provider.dart';
import 'package:shared_preferences/shared_preferences.dart';

class CryptSignature {
  final CertificateRepository certificateRepository;

  static Future<CryptSignature> getInstance({CertificateRepository? certificateRepository}) async {
    SharedPreferences sharedPreferences = await SharedPreferences.getInstance();
    CertificateRepository repository = certificateRepository ?? SPCertificateRepository(sharedPreferences, (data) => Certificate.fromJson(data));
    return CryptSignature._(repository);
  }

  CryptSignature._(this.certificateRepository);

  /// Открыть экран выбора сертификата и подписать
  /// В случает подписи PKCS7 на Android возвращает [PKCS7SignResult]
  /// В случает подписи XML возвращает [XMLDSIGSignResult]
  /// Возвращает [SignResult] для всеъ остальных
  Future<T?> interface<T extends SignResult>(BuildContext context, InterfaceRequest<T> interfaceRequest, {CryptSignatureTheme? theme}) async {
    NavigatorState navigator = Navigator.of(context);
    Directory directory = await getApplicationDocumentsDirectory();
    await Directory('${directory.path}/certificates').create();

    T? result = await navigator.push(
      FadePageRoute(
        builder: (context) => MultiProvider(
          providers: [
            Provider<CryptSignatureProvider>(create: (context) => CryptSignatureProvider(context, theme ?? CryptSignatureTheme(), interfaceRequest)),
            Provider<CertificateRepository>(create: (context) => certificateRepository),
            ChangeNotifierProvider<LockService>(create: (context) => LockService()),
            ChangeNotifierProvider<LicenseService>(create: (context) => LicenseService(context.read<LockService>())),
          ],
          builder: (context, child) => const HomeWidget(),
        ),
      ),
    );

    return result;
  }

  /// Инициализировать криптопровайдер
  Future<bool> initCSP() => Native.initCSP();

  /// Установить новую лицензию
  Future<License> setLicense(String license) => Native.setLicense(license);

  /// Получить информацию о текущей лицензии
  Future<License> getLicense() => Native.getLicense();

  /// Добавить сертификат в хранилище
  Future<Certificate> addCertificate(File file, String password) => Native.addCertificate(file, password);

  /// Вычислить хэш сообщения/документа
  Future<DigestResult> digest(Certificate certificate, String password, String message) => Native.digest(certificate, password, message);

  /// Вычислить подпись хэша
  Future<SignResult> sign(Certificate certificate, String password, String digest) => Native.sign(certificate, password, digest);

  /// Создать [PKCS7] и атрибуты подписи на основе [digest]
  Future<PKCS7> createPKCS7(Certificate certificate, String password, String digest) => Native.createPKCS7(certificate, password, digest);

  /// Прикрепить к [pkcs7] сигнатуру [signature]
  Future<PKCS7> addSignatureToPKCS7(PKCS7 pkcs7, String signature) => Native.addSignatureToPKCS7(pkcs7, signature);

  /// Получить список сертификатов, добавленных пользователем
  FutureOr<List<Certificate>> getCertificates() => certificateRepository.getEntities();

  /// Очистить список сертификатов
  Future<void> clear() async {
    Directory applicationDirectory = await getApplicationDocumentsDirectory();
    Directory directory = Directory('${applicationDirectory.path}/certificates');

    if (directory.existsSync()) await directory.delete(recursive: true);
    await certificateRepository.clear();
  }
}
