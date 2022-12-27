import 'package:crypt_signature/src/utils/extensions.dart';

class PKCS7 {
  final String content;
  final String signedAttributes;

  PKCS7({required this.content, required this.signedAttributes});

  @override
  String toString() => "Контент: ${content.truncate()}\nАтрибуты подписи: ${signedAttributes.truncate()}";
}
