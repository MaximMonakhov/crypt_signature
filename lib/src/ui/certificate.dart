import 'dart:io';

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
  Widget build(BuildContext context) => GestureDetector(
        onTap: () {
          context.read<CertificateService>().sign(context, certificate);
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
