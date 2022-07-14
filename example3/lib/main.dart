// ignore_for_file: use_key_in_widget_constructors, prefer_const_constructors_in_immutables, library_private_types_in_public_api

import 'package:crypt_signature/crypt_signature.dart';
import 'package:crypt_signature/models/interface_request.dart';
import 'package:crypt_signature/models/pkcs7.dart';
import 'package:crypt_signature/models/sign_result.dart';
import 'package:crypt_signature/models/certificate.dart';
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
  MyHomePage({Key key}) : super(key: key);

  @override
  _MyHomePageState createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  String data = "0J/Rg9GC0LjQvSDQstC+0YA=";

  Future<String> getMessage(Certificate certificate) async {
    await Future.delayed(const Duration(seconds: 1));
    return data;
  }

  Future<String> getDigest(Certificate certificate) async {
    await Future.delayed(const Duration(seconds: 1));
    return data;
  }

  // Future<String> getSignedAttributes(Certificate certificate, String digest) async {
  //   await Future.delayed(Duration(seconds: 1));
  //   ApiResponse<PKCS7> response = await CryptSignature.createPKCS7(certificate, "123", digest);
  //   return response.data.signedAttributes;
  // }

  void showResultDialog(String data) {
    if (data == null) return;
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
                SignResult result =
                    await CryptSignature.interface(context, MessageInterfaceRequest(data), title: "Войти по сертификату", hint: "Выберите сертификат");

                showResultDialog(result?.signature);
              },
              child: const Text("MessageInterfaceRequest"),
            ),
            OutlinedButton(
              onPressed: () async {
                PKCS7 result = await CryptSignature.interface(context, PKCS7InterfaceRequest(getMessage));

                showResultDialog(result?.content);
              },
              child: const Text("PKCS7InterfaceRequest"),
            ),
            OutlinedButton(
              onPressed: () async {
                PKCS7 result = await CryptSignature.interface(context, PKCS7HASHInterfaceRequest(getDigest));

                showResultDialog(result?.content);
              },
              child: const Text("PKCS7HASHInterfaceRequest"),
            ),
          ],
        ),
      ),
    );
  }
}
