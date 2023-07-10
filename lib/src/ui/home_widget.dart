import 'package:crypt_signature/src/core/builder/async_builder.dart';
import 'package:crypt_signature/src/native/native.dart';
import 'package:crypt_signature/src/providers/crypt_signature_provider.dart';
import 'package:crypt_signature/src/services/license_service.dart';
import 'package:crypt_signature/src/ui/certificates_view.dart';
import 'package:crypt_signature/src/ui/license_widget.dart';
import 'package:crypt_signature/src/ui/locker_widget.dart';
import 'package:flutter/material.dart';
import 'package:provider/provider.dart';

class HomeWidget extends StatelessWidget {
  const HomeWidget();

  PreferredSize appBar(BuildContext context) => PreferredSize(
        preferredSize: const Size.fromHeight(40),
        child: AppBar(
          centerTitle: true,
          elevation: 0,
          title: Text(
            context.read<CryptSignatureProvider>().theme.title,
            style: TextStyle(color: context.read<CryptSignatureProvider>().theme.themeData?.brightness == Brightness.dark ? Colors.white : Colors.black87),
          ),
          actions: [
            Center(
              child: Padding(
                padding: const EdgeInsets.only(right: 15.0),
                child: Text(
                  "5.0.42798",
                  style: TextStyle(color: Colors.grey.withOpacity(0.5)),
                ),
              ),
            )
          ],
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

  Future<bool> init(BuildContext context) async {
    bool init = await Native.initCSP();
    if (init) {
      try {
        context.read<LicenseService>().license = await Native.getLicense();
        // ignore: avoid_catches_without_on_clauses
      } catch (_) {}
    }

    return true;
  }

  @override
  Widget build(BuildContext context) => MaterialApp(
        debugShowCheckedModeBanner: false,
        theme: context.read<CryptSignatureProvider>().theme.themeData ??
            ThemeData(
              brightness: Brightness.light,
              splashFactory: InkRipple.splashFactory,
              splashColor: const Color.fromARGB(255, 230, 230, 230).withOpacity(0.10),
              appBarTheme: const AppBarTheme(
                elevation: 0,
                color: Color.fromRGBO(250, 250, 250, 1),
              ),
              fontFamily: 'SegoeUI',
              primaryColor: const Color.fromRGBO(53, 66, 95, 1),
              colorScheme: const ColorScheme.light(
                primary: Color.fromRGBO(53, 66, 95, 1),
                secondary: Color.fromRGBO(106, 147, 245, 1),
              ),
              dividerColor: Colors.black26,
              scaffoldBackgroundColor: const Color.fromRGBO(250, 250, 250, 1),
              bottomAppBarTheme: const BottomAppBarTheme(color: Colors.white),
              dialogBackgroundColor: Colors.grey,
              textSelectionTheme: const TextSelectionThemeData(
                cursorColor: Colors.black87,
                selectionColor: Colors.grey,
                selectionHandleColor: Color.fromRGBO(73, 93, 135, 1),
              ),
            ),
        home: Scaffold(
          appBar: appBar(context),
          body: Stack(
            children: [
              AsyncFutureBuilder<void>(
                wrapWithList: false,
                scrollbar: false,
                alwaysScrollableScrollPhysics: false,
                refreshIndicator: false,
                getObject: () => init(context),
                builder: (context, entity) => [
                  Column(
                    children: const [
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
