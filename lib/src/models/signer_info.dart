import 'dart:convert';

import 'package:asn1lib/asn1lib.dart';
import 'package:crypt_signature/crypt_signature.dart';
import 'package:crypt_signature/src/models/signed_attribute.dart';

class SignerInfo {
  final ASN1ObjectIdentifier digestIdentifier;
  final SignedAttribute signedAttribute;
  final ASN1Sequence sequence;
  String? signature;

  factory SignerInfo(Certificate certificate, {required String digest, required String certificateDigest, String? signature, DateTime? signTime}) {
    ASN1ObjectIdentifier digestIdentifier = ASN1ObjectIdentifier(certificate.algorithm.hashOID.split(".").map((e) => int.parse(e)).toList());
    ASN1ObjectIdentifier signatureIdentifier = ASN1ObjectIdentifier(certificate.algorithm.publicKeyOID.split(".").map((e) => int.parse(e)).toList());
    SignedAttribute signedAttribute = SignedAttribute(certificate, digestIdentifier, digest: digest, certificateDigest: certificateDigest, signTime: signTime);

    ASN1Sequence root = ASN1Sequence();
    // Версия
    root.add(ASN1Integer.fromInt(1));
    // Издатель
    root.add(
      ASN1Sequence()
        ..add(certificate.x509certificate.tbsCertificate.issuer)
        ..add(ASN1Integer(BigInt.parse(certificate.serialNumber, radix: 16))),
    );
    // Digest Algorithm
    root.add(
      ASN1Sequence()
        ..add(digestIdentifier)
        ..add(ASN1Null()),
    );
    // Authenticated Attributes
    root.add(signedAttribute.sequence);
    // Signature Algorithm
    root.add(
      ASN1Sequence()
        ..add(signatureIdentifier)
        ..add(ASN1Null()),
    );
    // Signature
    if (signature != null) root.add(ASN1OctetString(base64.decode(signature)));

    return SignerInfo._(root, signedAttribute, digestIdentifier, signature: signature);
  }

  SignerInfo._(this.sequence, this.signedAttribute, this.digestIdentifier, {this.signature});

  void attachSignature(String signature) {
    if (this.signature != null) throw Exception("Для SignerInfo уже привязанна сигнатура");
    this.signature = signature;
    sequence.add(ASN1OctetString(base64.decode(signature)));
  }
}
