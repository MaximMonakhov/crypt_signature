import 'dart:convert';

import 'package:crypt_signature/crypt_signature.dart';
import 'package:flutter/material.dart';

void main() {
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  static final GlobalKey<NavigatorState> navigatorKey = GlobalKey(debugLabel: "Main Navigator");

  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      navigatorKey: navigatorKey,
      title: 'Flutter Demo',
      theme: ThemeData(
        primarySwatch: Colors.blue,
      ),
      home: MyHomePage(),
    );
  }
}

class MyHomePage extends StatefulWidget {
  MyHomePage({super.key});

  @override
  _MyHomePageState createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  Future<String> getMessage(Certificate certificate) async {
    await Future.delayed(const Duration(seconds: 1));
    return base64.encode(utf8.encode("Данные на подпись"));
  }

  Future<String> getDigest(Certificate certificate) async {
    await Future.delayed(const Duration(seconds: 1));
    return "CXjNBON6v7foWjJ+mFXglgiPvXbcqYsQiErTnftDGRY="; // ХЭШ 2012 256 от "VEVTVA==" или "TEST"
  }

  void showResultDialog(String data) {
    showDialog(
      context: context,
      builder: (BuildContext context) {
        return AlertDialog(
          backgroundColor: Colors.white,
          titlePadding: const EdgeInsets.symmetric(vertical: 20.0),
          contentPadding: const EdgeInsets.only(left: 20, right: 20.0, bottom: 20.0, top: 20.0),
          shape: const RoundedRectangleBorder(borderRadius: BorderRadius.all(Radius.circular(10))),
          content: Text(
            data,
            style: const TextStyle(fontSize: 12, color: Colors.black87),
          ),
        );
      },
    );
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text("Signature"),
        centerTitle: true,
      ),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          crossAxisAlignment: CrossAxisAlignment.center,
          children: [
            OutlinedButton(
              onPressed: () async {
                SignResult? result = await CryptSignature.interface(context, MessageSignRequest(base64.encode(utf8.encode("Данные на подпись"))),
                    title: "Войти по сертификату", hint: "Выберите сертификат");

                showResultDialog(result.toString());
              },
              child: const Text("MessageSignRequest"),
            ),
            OutlinedButton(
              onPressed: () async {
                PKCS7SignResult? result = await CryptSignature.interface(context, PKCS7MessageSignRequest(getMessage));

                showResultDialog(result.toString());
              },
              child: const Text("PKCS7MessageSignRequest"),
            ),
            OutlinedButton(
              onPressed: () async {
                PKCS7SignResult? result = await CryptSignature.interface(context, PKCS7HASHSignRequest(getDigest));

                showResultDialog(result.toString());
              },
              child: const Text("PKCS7HASHSignRequest"),
            ),
            OutlinedButton(
              onPressed: () async {
                // TODO: доделать пример
                // XMLDSIGSignResult? result = await CryptSignature.interface(context, XMLSignRequest());

                // showResultDialog(result.toString());
              },
              child: const Text("XMLSignRequest"),
            ),
          ],
        ),
      ),
    );
  }
}
