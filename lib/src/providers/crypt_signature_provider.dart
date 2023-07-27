import 'package:crypt_signature/src/models/sign_request.dart';
import 'package:crypt_signature/src/utils/crypt_signature_theme.dart';
import 'package:flutter/widgets.dart';

class CryptSignatureProvider {
  final BuildContext rootContext;
  final CryptSignatureTheme theme;
  final SignRequest signRequest;

  CryptSignatureProvider(this.rootContext, this.theme, this.signRequest);
}
