import 'dart:io';

import 'package:crypt_signature/bloc/native.dart';
import 'package:crypt_signature/bloc/ui.dart';
import 'package:crypt_signature/models/certificate.dart';
import 'package:crypt_signature/ui/certificate.dart';
import 'package:crypt_signature/ui/error.dart';
import 'package:crypt_signature/ui/lock.dart';
import 'package:file_picker/file_picker.dart';
import 'package:flutter/material.dart';
import 'package:api_event/api_event.dart';
import 'package:path_provider/path_provider.dart';

class Certificates extends StatefulWidget {
  final String hint;
  final Future<String> Function(String rawCertificate) onCertificateSelected;

  const Certificates({Key key, this.onCertificateSelected, this.hint})
      : super(key: key);

  @override
  _CertificatesState createState() => _CertificatesState();
}

class _CertificatesState extends State<Certificates> {
  Event<List<Certificate>> certificates = Event<List<Certificate>>();

  @override
  void initState() {
    _getCertificates();
    super.initState();
  }

  _getCertificates() {
    List<Certificate> list = Certificate.storage.get();
    certificates.publish(list);
  }

  installCertificate() async {
    FilePickerResult filePickerResult = await FilePicker.platform
        .pickFiles(type: FileType.custom, allowedExtensions: ["pfx"]);

    if (filePickerResult != null) {
      File file = File(filePickerResult.files.single.path);
      String password = await showInputDialog(
          context,
          "Введите пароль для\n распаковки сертификата",
          "Пароль",
          true,
          TextInputType.visiblePassword);

      if (password != null && password.isNotEmpty) {
        ApiResponse<Certificate> response =
            await Native.installCertificate(file, password);
        if (response.status == Status.COMPLETED) {
          if (!Certificate.storage.add(response.data))
            showError(context, "Сертификат уже добавлен");
          else
            _getCertificates();
        } else
          showError(context,
              "Не удалось добавить сертификат.\nПроверьте правильность введенного пароля",
              details: response.message);
      }
    }
  }

  removeCertificate(Certificate certificate) async {
    Directory directory = await getApplicationDocumentsDirectory();
    String filePath =
        directory.path + "/certificates/" + certificate.uuid + ".pfx";
    File file = File(filePath);
    file.delete();

    Certificate.storage.remove(certificate);

    _getCertificates();
  }

  @override
  Widget build(BuildContext context) {
    return StreamBuilder<bool>(
      stream: UI.lockScreenEvent.stream,
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

        return Stack(
          children: [
            StreamBuilder<List<Certificate>>(
                stream: certificates.stream,
                builder: (context, snapshot) {
                  if (!snapshot.hasData)
                    return Center(
                      child: Container(
                        width: 20.0,
                        height: 20.0,
                        child: CircularProgressIndicator(
                          strokeWidth: 1,
                          backgroundColor: Colors.transparent,
                          valueColor:
                              AlwaysStoppedAnimation<Color>(Colors.black),
                        ),
                      ),
                    );

                  return Stack(
                    alignment: Alignment.bottomCenter,
                    children: [
                      snapshot.data.isNotEmpty
                          ? Column(
                              children: [
                                Padding(
                                    padding:
                                        EdgeInsets.symmetric(vertical: 5.0)),
                                Text(widget.hint),
                                Expanded(
                                  child: ListView.builder(
                                      padding:
                                          EdgeInsets.symmetric(vertical: 10.0),
                                      physics: BouncingScrollPhysics(),
                                      itemCount: snapshot.data.length,
                                      itemBuilder: (context, index) =>
                                          CertificateWidget(
                                            snapshot.data[index],
                                            removeCertificate,
                                            onCertificateSelected:
                                                widget.onCertificateSelected,
                                          )),
                                ),
                              ],
                            )
                          : Center(child: Text("Список сертификатов пуст")),
                      GestureDetector(
                        onTap: installCertificate,
                        child: Container(
                          margin: EdgeInsets.only(bottom: 40.0),
                          padding: EdgeInsets.symmetric(
                              horizontal: 40.0, vertical: 10.0),
                          decoration: BoxDecoration(
                            color: Color.fromRGBO(106, 147, 245, 1),
                            borderRadius: BorderRadius.circular(10.0),
                          ),
                          child: Text(
                            "Добавить сертификат",
                            textAlign: TextAlign.center,
                            style: TextStyle(color: Colors.white),
                          ),
                        ),
                      ),
                    ],
                  );
                }),
            snapshot.data ? LockWidget() : Container()
          ],
        );
      },
    );
  }
}
