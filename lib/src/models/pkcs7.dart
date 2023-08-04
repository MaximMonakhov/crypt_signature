import 'dart:convert';

import 'package:asn1lib/asn1lib.dart';
import 'package:crypt_signature/crypt_signature.dart';
import 'package:crypt_signature/src/models/signer_info.dart';
import 'package:crypt_signature/src/utils/extensions/extensions.dart';

const int CONTEXT_SPECIFIC_TYPE = 0xA0;

/// В данном процессе возникает ошибка:
/// 1. Получить байты
/// 2. Прикрепить сигнатуру
/// 3. Получить байты
/// Из-за того, что ASN1 пакет зачем-то запоминает байты
class PKCS7 {
  final Certificate certificate;
  final SignerInfo signerInfo;
  final String digest;
  final String certificateDigest;
  final String? message;
  final bool detached;

  PKCS7(this.certificate, this.digest, this.certificateDigest, {String? signature, DateTime? signTime, this.message})
      : signerInfo = SignerInfo(certificate, digest: digest, certificateDigest: certificateDigest, signature: signature, signTime: signTime),
        detached = message == null;

  ASN1Sequence get root {
    ASN1Sequence root = ASN1Sequence();
    root.add(ASN1ObjectIdentifier([1, 2, 840, 113549, 1, 7, 2]));

    ASN1Sequence data = ASN1Sequence();
    // Версия
    data.add(ASN1Integer.fromInt(1));
    // DigestAlgorithms
    data.add(
      ASN1Set()
        ..add(
          ASN1Sequence()
            ..add(signerInfo.digestIdentifier)
            ..add(ASN1Null()),
        ),
    );
    // ContentInfo
    ASN1Sequence encapsulatedContentInfo = ASN1Sequence()..add(ASN1ObjectIdentifier([1, 2, 840, 113549, 1, 7, 1]));
    if (!detached) encapsulatedContentInfo.add(ASN1Sequence(tag: CONTEXT_SPECIFIC_TYPE)..add(ASN1OctetString(base64.decode(message!))));
    data.add(encapsulatedContentInfo);
    // Certificate
    data.add(ASN1OctetString(base64.decode(certificate.certificate), tag: CONTEXT_SPECIFIC_TYPE));
    // SignerInfo
    data.add(ASN1Set()..add(signerInfo.sequence));

    root.add(ASN1OctetString(data.encodedBytes, tag: CONTEXT_SPECIFIC_TYPE));

    return root;
  }

  String get encoded => base64.encode(root.encodedBytes);

  @override
  String toString() =>
      "PKCS7:\nCertificate: ${certificate.certificate.truncate()}\nDigest: ${digest.truncate()}\nSignature: ${(signerInfo.signature ?? '-').truncate()}\nRoot: $root";
}
