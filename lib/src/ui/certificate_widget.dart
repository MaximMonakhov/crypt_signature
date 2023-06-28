import 'dart:io';

import 'package:crypt_signature/src/core/interface/smooth_button.dart';
import 'package:crypt_signature/src/core/interface/smooth_card.dart';
import 'package:crypt_signature/src/models/certificate.dart';
import 'package:crypt_signature/src/services/certificate_service.dart';
import 'package:crypt_signature/src/utils/crypt_signature_icons_icons.dart';
import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:provider/provider.dart';

class CertificateWidget extends StatelessWidget {
  final Certificate certificate;
  final void Function(Certificate) removeCallback;

  const CertificateWidget(this.certificate, this.removeCallback, {super.key});

  @override
  Widget build(BuildContext context) => SmoothCard(
        padding: const EdgeInsets.only(left: 10.0, right: 10.0, top: 5.0),
        onTap: () {
          context.read<CertificateService>().sign(context, certificate);
        },
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: <Widget>[
            Row(
              mainAxisAlignment: MainAxisAlignment.spaceBetween,
              children: [
                Icon(
                  CryptSignatureIcons.license,
                  size: 20,
                  color: Theme.of(context).colorScheme.primary,
                ),
                const Padding(padding: EdgeInsets.symmetric(horizontal: 5.0)),
                Expanded(
                  child: FittedBox(
                    alignment: Alignment.centerLeft,
                    fit: BoxFit.scaleDown,
                    child: Text(
                      "№${certificate.serialNumber}",
                      style: const TextStyle(fontSize: 12),
                    ),
                  ),
                ),
                const Padding(padding: EdgeInsets.symmetric(horizontal: 2.5)),
                SmoothButton(
                  onTap: () => removeCallback(certificate),
                  child: Container(
                    padding: const EdgeInsets.all(7.5),
                    child: const Icon(
                      Icons.clear,
                      size: 14,
                      color: CupertinoColors.systemRed,
                    ),
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
                const Text("Действителен до", style: TextStyle(fontSize: 12)),
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
              child: Padding(
                padding: const EdgeInsets.symmetric(vertical: 10.0),
                child: SmoothButton(
                  onTap: () {
                    showDialog(
                      context: context,
                      builder: (BuildContext context) => AlertDialog(
                        backgroundColor: Theme.of(context).scaffoldBackgroundColor,
                        titlePadding: const EdgeInsets.symmetric(vertical: 20.0),
                        contentPadding: const EdgeInsets.only(left: 20, right: 20.0, bottom: 20.0),
                        shape: const RoundedRectangleBorder(borderRadius: BorderRadius.all(Radius.circular(10))),
                        title: const Text(
                          "Идентифицирующие сведения",
                          style: TextStyle(fontSize: 14),
                          textAlign: TextAlign.center,
                          maxLines: 10,
                        ),
                        content: Text(
                          certificate.subjectDN,
                          style: const TextStyle(fontSize: 12),
                        ),
                      ),
                    );
                  },
                  child: Padding(
                    padding: const EdgeInsets.symmetric(vertical: 5.0, horizontal: 10.0),
                    child: Text(
                      "Просмотреть идентифицирующие сведения",
                      style: TextStyle(
                        fontSize: 12,
                        color: Theme.of(context).colorScheme.secondary,
                        fontWeight: FontWeight.bold,
                      ),
                    ),
                  ),
                ),
              ),
            ),
          ],
        ),
      );
}
