import 'package:crypt_signature/crypt_signature.dart';
import 'package:crypt_signature/src/native/native.dart';
import 'package:crypt_signature/src/services/lock_service.dart';
import 'package:crypt_signature/src/ui/dialogs.dart';
import 'package:crypt_signature/src/utils/exceptions/api_response_exception.dart';
import 'package:flutter/material.dart';
import 'package:mask_text_input_formatter/mask_text_input_formatter.dart';

class LicenseService extends ChangeNotifier {
  final LockService lockService;

  LicenseService(this.lockService, {License? license}) : _license = license;

  License? _license;
  License? get license => _license;

  set license(License? license) {
    _license = license;
    notifyListeners();
  }

  Future<void> getLicense(BuildContext context) async {
    try {
      lockService.lockScreen();
      license = await Native.getLicense();
    } on ApiResponseException catch (e) {
      showError(context, e.message, details: e.details);
    } finally {
      lockService.unlockScreen();
    }
  }

  Future<License?> setLicense(BuildContext context, String licenseNumber) async {
    try {
      lockService.lockScreen();
      await Future.delayed(const Duration(milliseconds: 500));
      License license = await Native.setLicense(licenseNumber);
      if (!license.status) throw ApiResponseException(license.message, null);
      this.license = license;
      return license;
    } on ApiResponseException catch (e) {
      showError(context, e.message, details: e.details);
    } finally {
      lockService.unlockScreen();
    }

    return null;
  }

  Future<void> checkLicense(BuildContext context) async {
    bool? licenseStatus = license?.status;
    if (licenseStatus == null || !licenseStatus) {
      await showError(context, "Лицензия не установлена");
      License? license = await setNewLicenseSheet(context);
      if (license == null) throw Exception("Лицензия не установлена");
    }
  }

  Future<License?> setNewLicenseSheet(BuildContext context) async {
    var maskFormatter = MaskTextInputFormatter(
      mask: '#####-#####-#####-#####-#####',
      filter: {"#": RegExp('[0-9+A-Z]')},
    );
    String? newLicense = await showInputDialog(
      context,
      "Введите вашу лицензию Крипто ПРО",
      "Номер лицензии",
      TextInputType.emailAddress,
      inputFormatters: [maskFormatter],
    );

    return newLicense != null && newLicense.isNotEmpty ? setLicense(context, newLicense) : null;
  }
}
