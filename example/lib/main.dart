import 'package:crypt_signature/crypt_signature.dart';
import 'package:crypt_signature/models/sign_result.dart';
import 'package:crypt_signature/models/certificate.dart';
import 'package:flutter/material.dart';

void main() {
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  static final GlobalKey<NavigatorState> navigatorKey =
      GlobalKey(debugLabel: "Main Navigator");

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

  Future<String> onCertificateSelected(Certificate certificate) async {
    await Future.delayed(Duration(seconds: 3));
    return data;
  }

  String result = "";

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text("Signature"),
        centerTitle: true,
      ),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          crossAxisAlignment: CrossAxisAlignment.center,
          children: [
            Column(
              children: [
                TextButton(
                  onPressed: () async {
                    SignResult result = await CryptSignature.sign(context,
                        data: data,
                        title: "Войти по сертификату",
                        hint: "Выберите сертификат");

                    if (result != null)
                      setState(() {
                        this.result = result.signature;
                      });

                    print(result);
                  },
                  child: Text("Подписать: " + data),
                ),
                Text(result ?? "")
              ],
            ),
            TextButton(
              onPressed: () async {
                SignResult result = await CryptSignature.sign(context,
                    onCertificateSelected: onCertificateSelected,
                    title: "Войти по сертификату",
                    hint: "Выберите сертификат");

                print(result.signature);
              },
              child: Text("Подписать отложенно: " + data),
            ),
          ],
        ),
      ),
    );
  }
}
