import 'package:crypt_signature/src/core/builder/async_builder.dart';
import 'package:crypt_signature/src/core/interface/smooth_button.dart';
import 'package:crypt_signature/src/native/native.dart';
import 'package:crypt_signature/src/providers/crypt_signature_provider.dart';
import 'package:crypt_signature/src/services/license_service.dart';
import 'package:crypt_signature/src/ui/certificates.dart';
import 'package:crypt_signature/src/ui/license_widget.dart';
import 'package:crypt_signature/src/ui/locker_widget.dart';
import 'package:flutter/material.dart';
import 'package:provider/provider.dart';

class HomeWidget extends StatelessWidget {
  const HomeWidget();

  PreferredSize appBar(BuildContext context) => PreferredSize(
        preferredSize: const Size.fromHeight(40),
        child: AppBar(
          backgroundColor: const Color.fromRGBO(250, 250, 250, 1),
          centerTitle: true,
          elevation: 0,
          title: Text(
            context.read<CryptSignatureProvider>().theme.title,
            style: TextStyle(
              color: context.read<CryptSignatureProvider>().theme.textColor,
            ),
          ),
          actions: const [Center(child: Padding(padding: EdgeInsets.only(right: 15.0), child: Text("5.0.42798", style: TextStyle(color: Colors.black26))))],
          leading: GestureDetector(
            behavior: HitTestBehavior.translucent,
            onTap: () => Navigator.of(context.read<CryptSignatureProvider>().rootContext).pop(),
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
      );

  // Future<bool> init() async {
  //   Future future = Future.wait([
  //     Native.initCSP(),
  //     context.read<LicenseService>(),
  //   ]);
  // }

  @override
  Widget build(BuildContext context) => MaterialApp(
        debugShowCheckedModeBanner: false,
        theme: ThemeData(
          scaffoldBackgroundColor: context.read<CryptSignatureProvider>().theme.backgroundColor,
          primaryColor: context.read<CryptSignatureProvider>().theme.primaryColor,
        ),
        home: Scaffold(
          appBar: appBar(context),
          body: Stack(
            children: [
              AsyncFutureBuilder<bool>(
                wrapWithList: false,
                scrollbar: false,
                alwaysScrollableScrollPhysics: false,
                refreshIndicator: false,
                getObject: () => Native.initCSP(),
                builder: (context, entity) => [
                  Column(
                    children: [
                      LicenseWidget(),
                      Expanded(child: CertificatesView()),
                    ],
                  ),
                ],
              ),
              const LockerWidget(),
            ],
          ),
        ),
      );
}
