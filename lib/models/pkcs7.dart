import 'package:crypt_signature/utils/extensions.dart';

class PKCS7 {
  final String content;
  final String signedAttributes;

  PKCS7({this.content, this.signedAttributes});

  @override
  String toString() => "PKCS7: ${content?.truncate()}\nАтрибуты подписи: ${signedAttributes?.truncate()}";
}
