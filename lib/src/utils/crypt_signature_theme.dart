import 'package:flutter/material.dart';

class CryptSignatureTheme {
  final ThemeData? themeData;
  final String title;
  final String hint;
  final ScrollPhysics scrollPhysics;

  CryptSignatureTheme({
    this.themeData,
    this.title = "Подпись",
    this.hint = "Выберите сертификат",
    ScrollPhysics? scrollPhysics,
  }) : scrollPhysics = scrollPhysics ?? const BouncingScrollPhysics();
}
