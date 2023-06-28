import 'package:crypt_signature/src/models/interface_request.dart';
import 'package:crypt_signature/src/utils/crypt_signature_theme.dart';
import 'package:flutter/widgets.dart';

class CryptSignatureProvider {
  final BuildContext rootContext;
  final CryptSignatureTheme theme;
  final InterfaceRequest interfaceRequest;

  CryptSignatureProvider(this.rootContext, this.theme, this.interfaceRequest);
}
