import 'dart:io';

import 'package:crypt_signature/src/core/services/base_change_notifier.dart';
import 'package:crypt_signature/src/models/certificate.dart';
import 'package:crypt_signature/src/models/interface_request.dart';
import 'package:crypt_signature/src/models/sign_result.dart';
import 'package:crypt_signature/src/native/native.dart';
import 'package:crypt_signature/src/providers/crypt_signature_provider.dart';
import 'package:crypt_signature/src/repositories/certificate_repository.dart';
import 'package:crypt_signature/src/services/license_service.dart';
import 'package:crypt_signature/src/services/lock_service.dart';
import 'package:crypt_signature/src/ui/dialogs.dart';
import 'package:crypt_signature/src/utils/exceptions/api_response_exception.dart';
import 'package:file_picker/file_picker.dart';
import 'package:flutter/widgets.dart';
import 'package:path_provider/path_provider.dart';
import 'package:provider/provider.dart';

class CertificateService extends BaseChangeNotifier<Certificate> {
  final CryptSignatureProvider cryptSignatureProvider;
  final LockService lockService;
  final LicenseService licenseService;

  CertificateService(CertificateRepository super.certificateRepository, this.cryptSignatureProvider, this.lockService, this.licenseService);

  Future<void> sign(BuildContext context, Certificate certificate) async {
    // Проверка, если лицензия не установлена, то дальше не пускаем
    // await licenseService.checkLicense(context);

    String? password = await askPassword(context, "Введите пароль для\n доступа к контейнеру приватного ключа");
    if (password == null || password.isEmpty) return;

    context.read<LockService>().lockScreen();
    await Future.delayed(const Duration(milliseconds: 500));

    final InterfaceRequest request = cryptSignatureProvider.interfaceRequest;
    try {
      final SignResult result = await request.signer(certificate, password);
      Navigator.of(cryptSignatureProvider.rootContext).pop(result);
    } on ApiResponseException catch (e) {
      showError(context, e.message, details: e.details);
    } on Exception catch (e) {
      showError(context, "Возникла ошибка при выполнении ЭП", details: e.toString());
    } finally {
      context.read<LockService>().unlockScreen();
    }
  }

  Future<String?> askPassword(BuildContext context, String title) => showInputDialog(
        context,
        title,
        "Пароль",
        TextInputType.visiblePassword,
        obscureText: true,
      );

  Future<Certificate?> addCertificate(BuildContext context) async {
    FilePickerResult? filePickerResult = await FilePicker.platform.pickFiles(type: FileType.custom, allowedExtensions: ["pfx"]);

    if (filePickerResult != null) {
      File file = File(filePickerResult.files.single.path!);
      String? password = await askPassword(context, "Введите пароль для\n распаковки сертификата");

      if (password != null && password.isNotEmpty) {
        try {
          context.read<LockService>().lockScreen();
          Certificate certificate = await Native.addCertificate(file, password);
          bool added = await (repository as CertificateRepository).add(certificate);
          if (!added) {
            showError(context, "Сертификат уже добавлен");
          } else {
            entities = null;
            return certificate;
          }
        } on ApiResponseException catch (e) {
          showError(context, e.message, details: e.details);
        } finally {
          context.read<LockService>().unlockScreen();
        }
      }
    }

    return null;
  }

  Future<void> removeCertificate(Certificate certificate) async {
    Directory directory = await getApplicationDocumentsDirectory();
    String filePath = "${directory.path}/certificates/${certificate.uuid}.pfx";
    File file = File(filePath);
    file.delete();

    await (repository as CertificateRepository).remove(certificate);
    entities = null;
  }
}
