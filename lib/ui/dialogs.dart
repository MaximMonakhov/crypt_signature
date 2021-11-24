import 'package:flutter/material.dart';
import 'package:flutter/services.dart';

Future<String> showInputDialog(
  BuildContext context,
  String message,
  String hintText,
  TextInputType keyboardType, {
  List<TextInputFormatter> inputFormatters,
  bool obscureText = false,
}) async {
  String value = await showDialog(
    context: context,
    builder: (BuildContext context) {
      TextEditingController controller = TextEditingController();
      return AlertDialog(
        backgroundColor: Colors.white,
        titlePadding: const EdgeInsets.symmetric(vertical: 20.0),
        contentPadding: const EdgeInsets.only(left: 20, right: 20.0, bottom: 5.0),
        shape: const RoundedRectangleBorder(borderRadius: BorderRadius.all(Radius.circular(10))),
        title: Text(
          message,
          style: const TextStyle(fontSize: 12, color: Colors.black),
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
                fillColor: const Color.fromRGBO(230, 236, 240, 1),
                hintMaxLines: 1,
                hintText: hintText,
                hintStyle: const TextStyle(color: Color.fromRGBO(134, 145, 173, 1), fontSize: 14.0),
                border: const OutlineInputBorder(borderRadius: BorderRadius.all(Radius.circular(10.0)), borderSide: BorderSide.none),
              ),
            ),
            const Padding(padding: EdgeInsets.symmetric(vertical: 5.0)),
            TextButton(
              child: const Text(
                "Подтвердить",
                style: TextStyle(
                  color: Color.fromRGBO(106, 147, 245, 1),
                ),
              ),
              onPressed: () {
                Navigator.of(context).pop(controller.text);
              },
            )
          ],
        ),
      );
    },
  );

  return value;
}

void showError(BuildContext context, String message, {String details}) {
  showDialog(
    context: context,
    builder: (BuildContext context) {
      return AlertDialog(
        titlePadding: const EdgeInsets.symmetric(vertical: 20.0),
        contentPadding: const EdgeInsets.only(left: 20, right: 20.0, bottom: 5.0),
        shape: const RoundedRectangleBorder(borderRadius: BorderRadius.all(Radius.circular(10))),
        title: Text(
          message,
          style: const TextStyle(fontSize: 12),
          textAlign: TextAlign.center,
          maxLines: 10,
        ),
        content: Column(
          mainAxisSize: MainAxisSize.min,
          children: [
            if (details != null)
              TextButton(
                child: const Text(
                  "Показать подробности",
                  style: TextStyle(
                    color: Color.fromRGBO(106, 147, 245, 1),
                  ),
                ),
                onPressed: () {
                  showError(context, details);
                },
              )
            else
              Container(),
            TextButton(
              child: const Text(
                "Ок",
                style: TextStyle(
                  color: Color.fromRGBO(106, 147, 245, 1),
                ),
              ),
              onPressed: () {
                Navigator.of(context).pop();
              },
            )
          ],
        ),
      );
    },
  );
}
