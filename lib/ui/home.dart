import 'dart:io';

import 'package:api_event/api_event.dart';
import 'package:crypt_signature/bloc/native.dart';
import 'package:crypt_signature/crypt_signature.dart';
import 'package:crypt_signature/models/certificate.dart';
import 'package:crypt_signature/ui/dialogs.dart';
import 'package:flutter/material.dart';
import 'package:flutter/services.dart';

import 'package:mask_text_input_formatter/mask_text_input_formatter.dart';

import 'certificates.dart';

class Home extends StatefulWidget {
  final String title;
  final String hint;
  final Future<String> Function(Certificate certificate) onCertificateSelected;
  const Home({
    Key key,
    this.onCertificateSelected,
    this.title = "Подпись",
    this.hint = "Выберите сертификат",
  }) : super(key: key);

  @override
  _HomeState createState() => _HomeState();
}

class _HomeState extends State<Home> {
  Event<int> csp = Event<int>();

  @override
  void initState() {
    Platform.isIOS ? _initCSP(null) : checkLicense();

    super.initState();
  }

  void checkLicense() {
    String license = CryptSignature.sharedPreferences.getString("license");

    if (license == null || license.isEmpty) {
      WidgetsBinding.instance.addPostFrameCallback((_) {
        setNewLicenseSheet();
      });
    } else {
      _initCSP(license);
    }
  }

  Future<void> setNewLicenseSheet() async {
    var maskFormatter = MaskTextInputFormatter(
      mask: '#####-#####-#####-#####-#####',
      filter: {"#": RegExp('[0-9+A-Z]')},
    );
    String newLicense = await showInputDialog(
      context,
      "Введите вашу лицензию Крипто ПРО",
      "Номер лицензии",
      TextInputType.emailAddress,
      inputFormatters: [maskFormatter],
    );

    if (newLicense != null && newLicense.isNotEmpty) {
      CryptSignature.sharedPreferences.setString("license", newLicense);
      _initCSP(newLicense);
    } else {
      csp.publish(Native.INIT_CSP_LICENSE_ERROR);
    }
  }

  Future<void> _initCSP(String license) async {
    int result = await Native.initCSP(license);
    csp.publish(result);
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      home: AnnotatedRegion<SystemUiOverlayStyle>(
        value: SystemUiOverlayStyle.dark,
        child: Scaffold(
          backgroundColor: const Color.fromRGBO(250, 250, 250, 1),
          appBar: PreferredSize(
            preferredSize: const Size.fromHeight(40),
            child: AppBar(
              backgroundColor: const Color.fromRGBO(250, 250, 250, 1),
              centerTitle: true,
              elevation: 0,
              title: Text(
                widget.title,
                style: const TextStyle(color: Colors.black),
              ),
              leading: GestureDetector(
                behavior: HitTestBehavior.translucent,
                onTap: () => Navigator.of(CryptSignature.rootContext).pop(),
                child: Container(
                  alignment: Alignment.centerRight,
                  child: const Text(
                    "Назад",
                    maxLines: 1,
                    style: TextStyle(color: Colors.redAccent),
                  ),
                ),
              ),
            ),
          ),
          body: StreamBuilder<int>(
            stream: csp.stream,
            builder: (context, snapshot) {
              if (!snapshot.hasData) {
                return const Center(
                  child: SizedBox(
                    width: 20.0,
                    height: 20.0,
                    child: CircularProgressIndicator(
                      strokeWidth: 1,
                      backgroundColor: Colors.transparent,
                      valueColor: AlwaysStoppedAnimation<Color>(Colors.black),
                    ),
                  ),
                );
              }

              return snapshot.data == Native.INIT_CSP_OK
                  ? Certificates(
                      hint: widget.hint,
                      onCertificateSelected: widget.onCertificateSelected,
                    )
                  : snapshot.data == Native.INIT_CSP_LICENSE_ERROR
                      ? Center(
                          child: Column(
                            mainAxisAlignment: MainAxisAlignment.center,
                            children: [
                              const Text("Неверная лицензия"),
                              GestureDetector(
                                behavior: HitTestBehavior.translucent,
                                onTap: () {
                                  setNewLicenseSheet();
                                },
                                child: const Padding(
                                  padding: EdgeInsets.all(20.0),
                                  child: Text(
                                    "Ввести лицензию заново",
                                    style: TextStyle(color: Colors.blue, fontWeight: FontWeight.bold),
                                  ),
                                ),
                              ),
                            ],
                          ),
                        )
                      : const Center(child: Text("Не удалось инициализировать провайдер"));
            },
          ),
        ),
      ),
    );
  }
}
