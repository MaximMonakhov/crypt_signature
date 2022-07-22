import 'dart:io';

import 'package:crypt_signature/crypt_signature_icons_icons.dart';
import 'package:crypt_signature/models/license.dart';
import 'package:crypt_signature/ui/license/inherited_license.dart';
import 'package:crypt_signature/ui/loading_widget.dart';
import 'package:flutter/material.dart';

class LicenseWidget extends StatelessWidget {
  const LicenseWidget({Key key}) : super(key: key);

  static const Map<String, String> types = {"0": "день", "1": "дня", "2": "дней"};

  String getNumSign(int num) {
    String numString = num.toString();
    int lastChar = int.parse(numString[numString.length - 1]);
    if (num > 10 && num < 20) return types["2"];
    if (lastChar == 1) return types["0"];
    if (lastChar >= 2 && lastChar <= 4) return types["1"];
    return types["2"];
  }

  @override
  Widget build(BuildContext context) {
    if (Platform.isIOS) return Container();
    License license = InheritedLicense.of(context).license;

    if (license == null) return const LoadingWidget();

    String successMessage;
    try {
      if (license.expiredThroughDays < 0) throw Exception();
      successMessage = "Лицензия активна и истекает через ${license.expiredThroughDays} ${getNumSign(license.expiredThroughDays)}";
    } catch (_) {
      successMessage = "Лицензия активна";
    }

    return Container(
      padding: EdgeInsets.only(left: 10.0, right: 10.0, bottom: license.status ? 15.0 : 0),
      color: const Color.fromRGBO(243, 241, 247, 1),
      child: license.status
          ? Column(
              children: [
                Row(
                  children: [
                    Expanded(
                      child: FittedBox(
                        fit: BoxFit.scaleDown,
                        alignment: Alignment.centerLeft,
                        child: SelectableText(
                          license.serialNumber,
                          style: const TextStyle(fontSize: 14, fontWeight: FontWeight.bold, color: Colors.black87),
                        ),
                      ),
                    ),
                    const Padding(padding: EdgeInsets.symmetric(horizontal: 5.0)),
                    TextButton(
                      onPressed: () {
                        InheritedLicense.of(context).setNewLicenseSheet();
                      },
                      child: const Text(
                        "Изменить",
                        style: TextStyle(color: Color.fromRGBO(106, 147, 245, 1)),
                      ),
                    )
                  ],
                ),
                Row(
                  children: [
                    const Icon(
                      CryptSignatureIcons.checkmark_cicle,
                      color: Colors.green,
                      size: 20,
                    ),
                    const Padding(padding: EdgeInsets.symmetric(horizontal: 5.0)),
                    Expanded(
                      child: FittedBox(
                        fit: BoxFit.scaleDown,
                        alignment: Alignment.centerLeft,
                        child: Text(
                          successMessage,
                          style: const TextStyle(fontSize: 14, color: Colors.black87),
                        ),
                      ),
                    ),
                  ],
                ),
              ],
            )
          : Row(
              children: [
                const Icon(
                  CryptSignatureIcons.cross_circle,
                  color: Colors.redAccent,
                  size: 20,
                ),
                const Padding(padding: EdgeInsets.symmetric(horizontal: 5.0)),
                Expanded(
                  child: FittedBox(
                    fit: BoxFit.scaleDown,
                    alignment: Alignment.centerLeft,
                    child: Text(
                      license.message,
                      style: const TextStyle(fontSize: 14, color: Colors.black87),
                    ),
                  ),
                ),
                const Padding(padding: EdgeInsets.symmetric(horizontal: 5.0)),
                TextButton(
                  onPressed: () {
                    InheritedLicense.of(context).setNewLicenseSheet();
                  },
                  child: const Text(
                    "Изменить",
                    style: TextStyle(color: Color.fromRGBO(106, 147, 245, 1)),
                  ),
                )
              ],
            ),
    );
  }
}
