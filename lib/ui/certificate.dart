import 'package:api_event/models/api_response.dart';
import 'package:crypt_signature/bloc/native.dart';
import 'package:crypt_signature/bloc/ui.dart';
import 'package:crypt_signature/crypt_signature.dart';
import 'package:crypt_signature/models/certificate.dart';
import 'package:crypt_signature/models/sign_result.dart';
import 'package:crypt_signature/ui/dialogs.dart';
import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';

class CertificateWidget extends StatelessWidget {
  final Certificate certificate;
  final Future<String> Function(Certificate certificate) onCertificateSelected;
  final void Function(Certificate) removeCallback;

  const CertificateWidget(this.certificate, this.removeCallback,
      {Key key, this.onCertificateSelected})
      : super(key: key);

  void signData(Certificate certificate, BuildContext context) async {
    String password = await showInputDialog(
        context,
        "Введите пароль для\n доступа к контейнеру приватного ключа",
        "Пароль",
        true,
        TextInputType.visiblePassword);

    if (password != null && password.isNotEmpty) {
      UI.lockScreen();
      ApiResponse response = await Native.sign(certificate, password);
      await Future.delayed(Duration(seconds: 1));
      UI.unlockScreen();

      if (response.status == Status.COMPLETED) {
        SignResult signResult =
            SignResult(certificate, Native.data, response.data);
        Navigator.of(CryptSignature.rootContext).pop(signResult);
      } else
        showError(context,
            "Возникла ошибка во время подписи.\nПроверьте правильность введенного пароля",
            details: response.message);
    }
  }

  void sign(Certificate certificate, BuildContext context) async {
    UI.lockScreen();
    Native.data = await onCertificateSelected(certificate);
    UI.unlockScreen();

    if (Native.data == null) {
      showError(context, "Возникла ошибка во время подписи");
      return;
    }

    String password = await showInputDialog(
        context,
        "Введите пароль для\n доступа к контейнеру приватного ключа",
        "Пароль",
        true,
        TextInputType.visiblePassword);

    if (password != null && password.isNotEmpty) {
      UI.lockScreen();
      ApiResponse response = await Native.sign(certificate, password);
      await Future.delayed(Duration(seconds: 1));
      UI.unlockScreen();
      if (response.status == Status.COMPLETED) {
        SignResult signResult =
            SignResult(certificate, Native.data, response.data);
        Navigator.of(CryptSignature.rootContext).pop(signResult);
      } else
        showError(context,
            "Возникла ошибка во время подписи.\nПроверьте правильность введенного пароля",
            details: response.message);
    }
  }

  @override
  Widget build(BuildContext context) {
    return GestureDetector(
      onTap: () {
        if (onCertificateSelected == null)
          signData(certificate, context);
        else
          sign(certificate, context);
      },
      child: Container(
        margin: EdgeInsets.symmetric(horizontal: 10, vertical: 5.0),
        padding:
            EdgeInsets.only(left: 15.0, right: 15.0, top: 10.0, bottom: 10.0),
        decoration: BoxDecoration(
            borderRadius: BorderRadius.circular(10.0),
            color: Colors.white,
            boxShadow: [
              BoxShadow(
                  color: Colors.black.withOpacity(0.1),
                  offset: Offset(0, 0),
                  blurRadius: 0.5,
                  spreadRadius: 0.05),
              BoxShadow(
                color: Colors.black.withOpacity(0.1),
                offset: Offset(0, 0),
                blurRadius: 5.0,
              ),
            ]),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: <Widget>[
            Row(
              mainAxisAlignment: MainAxisAlignment.spaceBetween,
              children: [
                Expanded(
                  child: Text(
                    "№" + certificate.serialNumber,
                    style: TextStyle(
                        letterSpacing: -1, fontSize: 12, color: Colors.grey),
                  ),
                ),
                GestureDetector(
                    behavior: HitTestBehavior.translucent,
                    onTap: () => removeCallback(certificate),
                    child: Padding(
                      padding: EdgeInsets.only(left: 10.0),
                      child: Icon(
                        Icons.clear,
                        size: 14,
                        color: CupertinoColors.systemRed,
                      ),
                    ))
              ],
            ),
            Text(
              "Алиас: " + certificate.alias,
              style: TextStyle(fontSize: 16, fontWeight: FontWeight.bold),
            ),
            Text("Дата окончания: " + certificate.notAfterDate,
                style: TextStyle(fontSize: 15, fontWeight: FontWeight.w600)),
            Text("Алгоритм публичного ключа: " + certificate.algorithm,
                style: TextStyle(fontSize: 14, fontWeight: FontWeight.w600)),
            Text(
              "Информация: " + certificate.subjectDN,
              style: TextStyle(fontSize: 12),
            ),
          ],
        ),
      ),
    );
  }
}
