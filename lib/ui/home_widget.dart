import 'package:crypt_signature/exceptions/api_response_exception.dart';
import 'package:crypt_signature/inherited_crypt_signature.dart';
import 'package:crypt_signature/native/native.dart';
import 'package:crypt_signature/ui/certificates.dart';
import 'package:crypt_signature/ui/error/error_view.dart';
import 'package:crypt_signature/ui/license/license_widget.dart';
import 'package:crypt_signature/ui/license/license_wrapper.dart';
import 'package:crypt_signature/ui/loading_widget.dart';
import 'package:crypt_signature/ui/locker/locker_widget.dart';
import 'package:crypt_signature/ui/locker/locker_wrapper.dart';
import 'package:flutter/material.dart';
import 'package:flutter/services.dart';

class HomeWidget extends StatelessWidget {
  final String title;
  final String hint;

  const HomeWidget({
    Key key,
    this.title = "Подпись",
    this.hint = "Выберите сертификат",
  }) : super(key: key);

  PreferredSize appBar(BuildContext context) => PreferredSize(
        preferredSize: const Size.fromHeight(40),
        child: AppBar(
          backgroundColor: const Color.fromRGBO(250, 250, 250, 1),
          centerTitle: true,
          elevation: 0,
          title: Text(
            title,
            style: const TextStyle(color: Colors.black87),
          ),
          leading: GestureDetector(
            behavior: HitTestBehavior.translucent,
            onTap: () => Navigator.of(InheritedCryptSignature.of(context).rootContext).pop(),
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

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      home: AnnotatedRegion<SystemUiOverlayStyle>(
        value: SystemUiOverlayStyle.dark,
        child: LockerWrapper(
          child: LicenseWrapper(
            child: Scaffold(
              backgroundColor: const Color.fromRGBO(250, 250, 250, 1),
              appBar: appBar(context),
              body: Stack(
                children: [
                  FutureBuilder<bool>(
                    future: Native.initCSP(),
                    builder: (context, snapshot) {
                      if (snapshot.hasError) return ErrorView(snapshot.error as ApiResponseException);
                      if (!snapshot.hasData) return const LoadingWidget();

                      return Column(children: [const LicenseWidget(), Expanded(child: Certificates(hint: hint))]);
                    },
                  ),
                  const LockerWidget(),
                ],
              ),
            ),
          ),
        ),
      ),
    );
  }
}
