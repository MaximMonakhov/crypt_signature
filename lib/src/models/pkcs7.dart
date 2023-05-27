import 'dart:convert';

import 'package:asn1lib/asn1lib.dart';
import 'package:crypt_signature/crypt_signature.dart';
import 'package:crypt_signature/src/models/signer_info.dart';

const int CONTEXT_SPECIFIC_TYPE = 0xA0;

class PKCS7 {
  final Certificate certificate;
  final String digest;
  final SignerInfo signerInfo;

  PKCS7(this.certificate, this.digest)
      : signerInfo = SignerInfo(certificate.serialNumber, certificate.algorithm, certificate.x509certificate.tbsCertificate.issuer.toAsn1(), digest);

  void attachSignature(String signature) => signerInfo.signature = signature;

  String get content {
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
    data.add(ASN1Sequence()..add(ASN1ObjectIdentifier([1, 2, 840, 113549, 1, 7, 1])));
    // Certificate
    data.add(ASN1OctetString(base64.decode(certificate.certificate), tag: CONTEXT_SPECIFIC_TYPE));
    // SignerInfo
    data.add(ASN1Set()..add(signerInfo.sequence));

    root.add(ASN1OctetString(data.encodedBytes, tag: CONTEXT_SPECIFIC_TYPE));

    return base64.encode(root.encodedBytes);
  }
}
