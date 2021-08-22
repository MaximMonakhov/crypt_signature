import 'package:flutter/material.dart';
import 'package:flutter/services.dart';

Future<String> showInputDialog(BuildContext context, String message,
    String hintText, bool obscureText, TextInputType keyboardType,
    {List<TextInputFormatter> inputFormatters}) async {
  String value = await showDialog(
    context: context,
    builder: (BuildContext context) {
      TextEditingController controller = new TextEditingController();
      return AlertDialog(
        titlePadding: EdgeInsets.symmetric(vertical: 20.0),
        contentPadding:
            EdgeInsets.only(left: 20, right: 20.0, top: 0, bottom: 5.0),
        shape: RoundedRectangleBorder(
            borderRadius: BorderRadius.all(Radius.circular(10))),
        title: Text(
          message,
          style: TextStyle(fontSize: 12),
          textAlign: TextAlign.center,
          maxLines: 10,
        ),
        content: Column(
          mainAxisSize: MainAxisSize.min,
          children: [
            TextField(
              controller: controller,
              maxLines: 1,
              inputFormatters: inputFormatters ?? [],
              autofocus: true,
              keyboardType: keyboardType,
              obscureText: obscureText,
              textAlign: TextAlign.center,
              style: TextStyle(
                  decoration: TextDecoration.none,
                  decorationColor: Colors.white.withOpacity(0)),
              decoration: InputDecoration(
                isDense: true,
                contentPadding:
                    EdgeInsets.only(left: 15, right: 15, top: 5, bottom: 5),
                filled: true,
                fillColor: Color.fromRGBO(230, 236, 240, 1),
                hintMaxLines: 1,
                hintText: hintText,
                hintStyle: TextStyle(
                    color: Color.fromRGBO(134, 145, 173, 1), fontSize: 14.0),
                border: OutlineInputBorder(
                    borderRadius: BorderRadius.all(Radius.circular(10.0)),
                    borderSide: BorderSide(width: 0, style: BorderStyle.none)),
              ),
            ),
            Padding(padding: EdgeInsets.symmetric(vertical: 5.0)),
            TextButton(
              child: Text(
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

showError(BuildContext context, String message, {String details}) {
  showDialog(
    context: context,
    builder: (BuildContext context) {
      return AlertDialog(
        titlePadding: EdgeInsets.symmetric(vertical: 20.0),
        contentPadding:
            EdgeInsets.only(left: 20, right: 20.0, top: 0, bottom: 5.0),
        shape: RoundedRectangleBorder(
            borderRadius: BorderRadius.all(Radius.circular(10))),
        title: Text(
          message,
          style: TextStyle(fontSize: 12),
          textAlign: TextAlign.center,
          maxLines: 10,
        ),
        content: Column(
          mainAxisSize: MainAxisSize.min,
          children: [
            details != null
                ? TextButton(
                    child: Text(
                      "Показать подробности",
                      style: TextStyle(
                        color: Color.fromRGBO(106, 147, 245, 1),
                      ),
                    ),
                    onPressed: () {
                      showError(context, details);
                    },
                  )
                : Container(),
            TextButton(
              child: Text(
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
