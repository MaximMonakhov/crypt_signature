import 'package:api_event/api_event.dart';
import 'package:crypt_signature/bloc/native.dart';
import 'package:crypt_signature/crypt_signature.dart';
import 'package:flutter/material.dart';
import 'package:flutter/services.dart';

import 'certificates.dart';

class Home extends StatefulWidget {
  final String title;
  final String hint;
  const Home(
      {Key key, this.title = "Подпись", this.hint = "Выберите сертификат"})
      : super(key: key);

  @override
  _HomeState createState() => _HomeState();
}

class _HomeState extends State<Home> {
  Event<bool> csp = new Event<bool>();

  @override
  void initState() {
    _initCSP();
    super.initState();
  }

  _initCSP() async {
    bool result = await Native.initCSP();
    csp.publish(result);
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      home: AnnotatedRegion<SystemUiOverlayStyle>(
        value: SystemUiOverlayStyle.dark,
        child: Scaffold(
          backgroundColor: Color.fromRGBO(250, 250, 250, 1),
          appBar: PreferredSize(
            preferredSize: Size.fromHeight(40),
            child: AppBar(
              backgroundColor: Color.fromRGBO(250, 250, 250, 1),
              centerTitle: true,
              elevation: 0,
              title: Text(
                widget.title,
                style: TextStyle(color: Colors.black),
              ),
              leading: GestureDetector(
                behavior: HitTestBehavior.translucent,
                onTap: () => Navigator.of(CryptSignature.rootContext).pop(),
                child: Container(
                    alignment: Alignment.centerRight,
                    child: Text(
                      "Назад",
                      maxLines: 1,
                      style: TextStyle(color: Colors.redAccent),
                    )),
              ),
            ),
          ),
          body: StreamBuilder<bool>(
              stream: csp.stream,
              builder: (context, snapshot) {
                if (!snapshot.hasData)
                  return Center(
                    child: Container(
                      width: 20.0,
                      height: 20.0,
                      child: CircularProgressIndicator(
                        strokeWidth: 1,
                        backgroundColor: Colors.transparent,
                        valueColor: AlwaysStoppedAnimation<Color>(Colors.black),
                      ),
                    ),
                  );

                return snapshot.data
                    ? Certificates(hint: widget.hint)
                    : Center(
                        child: Text("Не удалось инициализировать провайдер"));
              }),
        ),
      ),
    );
  }
}
