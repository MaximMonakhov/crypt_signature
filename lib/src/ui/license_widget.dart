import 'dart:io';

import 'package:crypt_signature/src/core/interface/smooth_button.dart';
import 'package:crypt_signature/src/models/license.dart';
import 'package:crypt_signature/src/services/license_service.dart';
import 'package:crypt_signature/src/utils/crypt_signature_icons_icons.dart';
import 'package:flutter/material.dart';
import 'package:provider/provider.dart';

class LicenseWidget extends StatelessWidget {
  const LicenseWidget({super.key});

  static const Map<String, String> types = {"0": "день", "1": "дня", "2": "дней"};

  String getNumSign(int num) {
    String numString = num.toString();
    int lastChar = int.parse(numString[numString.length - 1]);
    if (num > 10 && num < 20) return types["2"]!;
    if (lastChar == 1) return types["0"]!;
    if (lastChar >= 2 && lastChar <= 4) return types["1"]!;
    return types["2"]!;
  }

  @override
  Widget build(BuildContext context) {
    if (Platform.isIOS) return Container();
    License? license = Provider.of<LicenseService>(context).license;

    if (license == null) return const SizedBox.shrink();

    String successMessage;
    try {
      if (license.expiredThroughDays < 0) throw Exception();
      successMessage = "Лицензия активна и истекает через ${license.expiredThroughDays} ${getNumSign(license.expiredThroughDays)}";
    } on Exception catch (_) {
      successMessage = "Лицензия активна";
    }

    return Container(
      padding: const EdgeInsets.only(left: 20.0, right: 10.0, bottom: 10.0, top: 10.0),
      decoration: BoxDecoration(
        color: Theme.of(context).colorScheme.background,
        border: Border.symmetric(horizontal: BorderSide(color: Colors.grey.withOpacity(0.2))),
      ),
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
                          style: const TextStyle(fontSize: 14, fontWeight: FontWeight.bold),
                        ),
                      ),
                    ),
                    const Padding(padding: EdgeInsets.symmetric(horizontal: 5.0)),
                    SmoothButton(
                      onTap: () {
                        context.read<LicenseService>().setNewLicenseSheet(context);
                      },
                      child: Container(
                        padding: const EdgeInsets.symmetric(vertical: 5.0, horizontal: 10.0),
                        child: Text(
                          "Изменить",
                          style: TextStyle(
                            color: Theme.of(context).colorScheme.secondary,
                            fontWeight: FontWeight.bold,
                          ),
                        ),
                      ),
                    ),
                  ],
                ),
                const Padding(padding: EdgeInsets.symmetric(vertical: 2.5)),
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
                          style: const TextStyle(fontSize: 14),
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
                      style: const TextStyle(fontSize: 14),
                    ),
                  ),
                ),
                const Padding(padding: EdgeInsets.symmetric(horizontal: 5.0)),
                SmoothButton(
                  onTap: () {
                    context.read<LicenseService>().setNewLicenseSheet(context);
                  },
                  child: Container(
                    padding: const EdgeInsets.symmetric(vertical: 5.0, horizontal: 10.0),
                    child: Text(
                      "Изменить",
                      style: TextStyle(
                        color: Theme.of(context).colorScheme.secondary,
                        fontWeight: FontWeight.bold,
                      ),
                    ),
                  ),
                ),
                // TextButton(
                //   onPressed: () {
                //     context.read<LicenseService>().setNewLicenseSheet(context);
                //   },
                //   child: const Text(
                //     "Изменить",
                //     style: TextStyle(color: Color.fromRGBO(106, 147, 245, 1)),
                //   ),
                // )
              ],
            ),
    );
  }
}
