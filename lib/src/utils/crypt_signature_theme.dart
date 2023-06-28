import 'package:flutter/material.dart';

class CryptSignatureTheme {
  final String title;
  final String hint;
  final Color backgroundColor;
  final Color primaryColor;
  final Color textColor;
  final ScrollPhysics scrollPhysics;

  CryptSignatureTheme({
    ThemeData? themeData,
    this.title = "Подпись",
    this.hint = "Выберите сертификат",
    Color? backgroundColor,
    Color? primaryColor,
    Color? textColor,
    ScrollPhysics? scrollPhysics,
  })  : backgroundColor = backgroundColor ?? themeData?.scaffoldBackgroundColor ?? Colors.white,
        primaryColor = primaryColor ?? themeData?.primaryColor ?? const Color.fromRGBO(106, 147, 245, 1),
        textColor = textColor ?? themeData?.textTheme.bodyMedium?.color ?? Colors.black87,
        scrollPhysics = scrollPhysics ?? const BouncingScrollPhysics();
}
