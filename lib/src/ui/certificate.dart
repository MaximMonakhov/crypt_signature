// ignore_for_file: use_build_context_synchronously

import 'dart:io';

import 'package:crypt_signature/src/exceptions/api_response_exception.dart';
import 'package:crypt_signature/src/inherited_crypt_signature.dart';
import 'package:crypt_signature/src/models/certificate.dart';
import 'package:crypt_signature/src/models/interface_request.dart';
import 'package:crypt_signature/src/models/sign_result.dart';
import 'package:crypt_signature/src/ui/dialogs.dart';
import 'package:crypt_signature/src/ui/license/inherited_license.dart';
import 'package:crypt_signature/src/ui/locker/inherited_locker.dart';
import 'package:crypt_signature/src/utils/crypt_signature_icons_icons.dart';
import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';

class CertificateWidget extends StatelessWidget {
  final Certificate certificate;
  final void Function(Certificate) removeCallback;

  const CertificateWidget(this.certificate, this.removeCallback, {super.key});

  Future<String?> _askPassword(BuildContext context) => showInputDialog(
        context,
        "Введите пароль для\n доступа к контейнеру приватного ключа",
        "Пароль",
        TextInputType.visiblePassword,
        obscureText: true,
      );

  bool? getLicenseStatus(BuildContext context) => InheritedLicense.of(context).license?.status;

  Future<void> _sign(BuildContext context) async {
    // Проверка, если лицензия не установлена, то дальше не пускаем
    // bool licenseStatus = getLicenseStatus(context);
    // if (licenseStatus == null || !licenseStatus) {
    //   await showError(context, "Лицензия не установлена");
    //   InheritedLicense.of(context).setNewLicenseSheet();
    //   return;
    // }

    String? password = await _askPassword(context);
    if (password == null || password.isEmpty) return;

    InheritedLocker.of(context).lockScreen();

    final InheritedCryptSignature inherit = InheritedCryptSignature.of(context);
    final InterfaceRequest request = inherit.interfaceRequest;
    try {
      final SignResult result = await request.signer(certificate, password);
      Navigator.of(inherit.rootContext).pop(result);
    } on ApiResponseException catch (e) {
      showError(context, e.message, details: e.details);
    } on Exception catch (e) {
      showError(context, "Возникла ошибка при выполнении ЭП", details: e.toString());
    } finally {
      InheritedLocker.of(context).unlockScreen();
    }
  }

  @override
  Widget build(BuildContext context) => GestureDetector(
        onTap: () {
          _sign(context);
        },
        child: Container(
          margin: const EdgeInsets.symmetric(horizontal: 10, vertical: 5.0),
          padding: const EdgeInsets.only(left: 10.0, right: 10.0, top: 10.0),
          decoration: BoxDecoration(
            borderRadius: BorderRadius.circular(10.0),
            color: Colors.white,
            boxShadow: [
              BoxShadow(color: Colors.black.withOpacity(0.1), blurRadius: 0.5, spreadRadius: 0.05),
              BoxShadow(
                color: Colors.black.withOpacity(0.1),
                blurRadius: 5.0,
              ),
            ],
          ),
          child: Column(
            crossAxisAlignment: CrossAxisAlignment.start,
            children: <Widget>[
              Row(
                mainAxisAlignment: MainAxisAlignment.spaceBetween,
                children: [
                  const Icon(
                    CryptSignatureIcons.license,
                    size: 20,
                    color: Colors.black87,
                  ),
                  const Padding(padding: EdgeInsets.symmetric(horizontal: 5.0)),
                  Expanded(
                    child: Text(
                      "№${certificate.serialNumber}",
                      style: const TextStyle(letterSpacing: -1, fontSize: 12, color: Colors.black87),
                    ),
                  ),
                  GestureDetector(
                    behavior: HitTestBehavior.translucent,
                    onTap: () => removeCallback(certificate),
                    child: const Icon(
                      Icons.clear,
                      size: 14,
                      color: CupertinoColors.systemRed,
                    ),
                  ),
                ],
              ),
              const Padding(padding: EdgeInsets.symmetric(vertical: 5.0)),
              Row(
                mainAxisAlignment: MainAxisAlignment.spaceBetween,
                children: [
                  Text(Platform.isIOS ? "Имя контейнера" : "Алиас", style: const TextStyle(fontSize: 12)),
                  const Padding(padding: EdgeInsets.symmetric(horizontal: 5.0)),
                  Expanded(
                    child: FittedBox(
                      alignment: Alignment.centerRight,
                      fit: BoxFit.scaleDown,
                      child: Text(certificate.alias, style: const TextStyle(fontSize: 14, fontWeight: FontWeight.bold)),
                    ),
                  ),
                ],
              ),
              const Divider(height: 5),
              Row(
                mainAxisAlignment: MainAxisAlignment.spaceBetween,
                children: [
                  const Text("Действителен по", style: TextStyle(fontSize: 12)),
                  const Padding(padding: EdgeInsets.symmetric(horizontal: 5.0)),
                  Expanded(
                    child: FittedBox(
                      alignment: Alignment.centerRight,
                      fit: BoxFit.scaleDown,
                      child: Text(certificate.notAfterDate, style: const TextStyle(fontSize: 14, fontWeight: FontWeight.bold)),
                    ),
                  ),
                ],
              ),
              const Divider(height: 5),
              Row(
                mainAxisAlignment: MainAxisAlignment.spaceBetween,
                children: [
                  const Text("Алгоритм публичного ключа", style: TextStyle(fontSize: 12)),
                  const Padding(padding: EdgeInsets.symmetric(horizontal: 5.0)),
                  Expanded(
                    child: FittedBox(
                      alignment: Alignment.centerRight,
                      fit: BoxFit.scaleDown,
                      child: Text(certificate.algorithm.name, style: const TextStyle(fontSize: 14, fontWeight: FontWeight.bold)),
                    ),
                  ),
                ],
              ),
              Align(
                child: TextButton(
                  onPressed: () {
                    showDialog(
                      context: context,
                      builder: (BuildContext context) => AlertDialog(
                        backgroundColor: Colors.white,
                        titlePadding: const EdgeInsets.symmetric(vertical: 20.0),
                        contentPadding: const EdgeInsets.only(left: 20, right: 20.0, bottom: 20.0),
                        shape: const RoundedRectangleBorder(borderRadius: BorderRadius.all(Radius.circular(10))),
                        title: const Text(
                          "Идентифицирующие сведения",
                          style: TextStyle(fontSize: 14, color: Colors.black87),
                          textAlign: TextAlign.center,
                          maxLines: 10,
                        ),
                        content: Text(
                          certificate.subjectDN,
                          style: const TextStyle(fontSize: 12, color: Colors.black87),
                        ),
                      ),
                    );
                  },
                  child: const Text(
                    "Просмотреть идентифицирующие сведения",
                    style: TextStyle(
                      fontSize: 12,
                      color: Color.fromRGBO(106, 147, 245, 1),
                    ),
                  ),
                ),
              ),
            ],
          ),
        ),
      );
}
