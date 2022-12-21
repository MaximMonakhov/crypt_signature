import 'dart:io';

import 'package:crypt_signature/src/exceptions/api_response_exception.dart';
import 'package:crypt_signature/src/models/license.dart';
import 'package:crypt_signature/src/native/native.dart';
import 'package:crypt_signature/src/ui/dialogs.dart';
import 'package:crypt_signature/src/ui/license/inherited_license.dart';
import 'package:crypt_signature/src/ui/locker/inherited_locker.dart';
import 'package:flutter/material.dart';
import 'package:mask_text_input_formatter/mask_text_input_formatter.dart';

class LicenseWrapper extends StatefulWidget {
  final Widget child;
  const LicenseWrapper({required this.child, super.key});

  @override
  State<LicenseWrapper> createState() => _LicenseWrapperState();
}

class _LicenseWrapperState extends State<LicenseWrapper> {
  License? license;

  @override
  void initState() {
    if (Platform.isAndroid) {
      WidgetsBinding.instance.addPostFrameCallback((_) {
        getLicense();
      });
    }
    super.initState();
  }

  Future<void> getLicense() async {
    try {
      InheritedLocker.of(context).lockScreen();
      License license = await Native.getLicense();

      setState(() {
        this.license = license;
      });
    } on ApiResponseException catch (e) {
      showError(context, e.message, details: e.details);
    } finally {
      InheritedLocker.of(context).unlockScreen();
    }
  }

  Future<void> setLicense(String licenseNumber) async {
    try {
      InheritedLocker.of(context).lockScreen();
      License license = await Native.setLicense(licenseNumber);
      if (!license.status) throw ApiResponseException(license.message, null);
      setState(() {
        this.license = license;
      });
    } on ApiResponseException catch (e) {
      showError(context, e.message, details: e.details);
    } finally {
      InheritedLocker.of(context).unlockScreen();
    }
  }

  Future<void> setNewLicenseSheet() async {
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
    if (newLicense != null && newLicense.isNotEmpty) setLicense(newLicense);
  }

  @override
  Widget build(BuildContext context) => InheritedLicense(
        license: license,
        getLicense: getLicense,
        setLicense: setLicense,
        setNewLicenseSheet: setNewLicenseSheet,
        child: widget.child,
      );
}
