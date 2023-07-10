import 'package:crypt_signature/src/core/interface/smooth_button.dart';
import 'package:flutter/material.dart';
import 'package:flutter/services.dart';

Future<String?> showInputDialog(
  BuildContext context,
  String message,
  String hintText,
  TextInputType keyboardType, {
  List<TextInputFormatter>? inputFormatters,
  bool obscureText = false,
}) async {
  String? value = await showDialog(
    context: context,
    builder: (BuildContext context) {
      TextEditingController controller = TextEditingController();
      return AlertDialog(
        backgroundColor: Theme.of(context).scaffoldBackgroundColor,
        titlePadding: const EdgeInsets.symmetric(vertical: 20.0, horizontal: 10.0),
        contentPadding: const EdgeInsets.only(left: 20, right: 20.0, bottom: 5.0),
        shape: const RoundedRectangleBorder(borderRadius: BorderRadius.all(Radius.circular(10))),
        title: Text(
          message,
          style: const TextStyle(fontSize: 14),
          textAlign: TextAlign.center,
          maxLines: 10,
        ),
        content: Column(
          mainAxisSize: MainAxisSize.min,
          children: [
            TextField(
              controller: controller,
              inputFormatters: inputFormatters ?? [],
              autofocus: true,
              keyboardType: keyboardType,
              obscureText: obscureText,
              textAlign: TextAlign.center,
              style: TextStyle(decoration: TextDecoration.none, decorationColor: Colors.white.withOpacity(0)),
              decoration: InputDecoration(
                isDense: true,
                contentPadding: const EdgeInsets.only(left: 15, right: 15, top: 5, bottom: 5),
                filled: true,
                fillColor: Theme.of(context).brightness == Brightness.light ? const Color.fromRGBO(230, 236, 240, 1) : Theme.of(context).colorScheme.background,
                hintMaxLines: 1,
                hintText: hintText,
                hintStyle: const TextStyle(color: Color.fromRGBO(134, 145, 173, 1), fontSize: 14.0),
                border: const OutlineInputBorder(borderRadius: BorderRadius.all(Radius.circular(10.0)), borderSide: BorderSide.none),
              ),
            ),
            const Padding(padding: EdgeInsets.symmetric(vertical: 5.0)),
            SmoothButton(
              onTap: () {
                Navigator.of(context).pop(controller.text);
              },
              title: "Подтвердить",
            ),
            const Padding(padding: EdgeInsets.symmetric(vertical: 2.5)),
          ],
        ),
      );
    },
  );

  return value;
}

Future<void> showError(BuildContext context, String? message, {String? details}) => showDialog(
      context: context,
      builder: (BuildContext context) => AlertDialog(
        backgroundColor: Theme.of(context).scaffoldBackgroundColor,
        titlePadding: const EdgeInsets.symmetric(vertical: 20.0, horizontal: 10.0),
        contentPadding: const EdgeInsets.only(left: 20, right: 20.0, bottom: 5.0),
        shape: const RoundedRectangleBorder(borderRadius: BorderRadius.all(Radius.circular(10))),
        title: Text(
          message ?? "Ошибка",
          style: const TextStyle(fontSize: 14),
          textAlign: TextAlign.center,
          maxLines: 10,
        ),
        content: Column(
          mainAxisSize: MainAxisSize.min,
          children: [
            if (details != null)
              SmoothButton(
                onTap: () {
                  showError(context, details);
                },
                title: "Показать подробности",
              )
            else
              Container(),
            SmoothButton(
              onTap: () {
                Navigator.of(context).pop();
              },
              title: "Ок",
            ),
            const Padding(padding: EdgeInsets.symmetric(vertical: 5.0)),
          ],
        ),
      ),
    );
