import 'dart:convert';

import 'package:asn1lib/asn1lib.dart';
import 'package:crypt_signature/crypt_signature.dart';
import 'package:crypt_signature/src/models/pkcs7.dart';

class SignerInfo {
  final String serialNumber;
  final Algorithm algorithm;
  final ASN1Sequence issuer;
  final String digest;
  final ASN1ObjectIdentifier digestIdentifier;
  final ASN1ObjectIdentifier signatureIdentifier;
  final DateTime signTime;
  String? signature;

  SignerInfo(this.serialNumber, this.algorithm, this.issuer, this.digest, {this.signature, DateTime? signTime})
      : digestIdentifier = ASN1ObjectIdentifier(algorithm.hashOID.split(".").map((e) => int.parse(e)).toList()),
        signatureIdentifier = ASN1ObjectIdentifier(algorithm.signatureOID.split(".").map((e) => int.parse(e)).toList()),
        signTime = signTime ?? DateTime.now().toUtc();

  ASN1Sequence get sequence {
    ASN1Sequence root = ASN1Sequence();
    // Версия
    root.add(ASN1Integer.fromInt(1));
    // Издатель
    root.add(
      ASN1Sequence()
        ..add(issuer)
        ..add(ASN1Integer(BigInt.parse(serialNumber, radix: 16))),
    );
    // Digest Algorithm
    root.add(
      ASN1Sequence()
        ..add(digestIdentifier)
        ..add(ASN1Null()),
    );
    // Authenticated Attributes
    List<ASN1Sequence> authenticatedAttributes = [
      ASN1Sequence()
        ..add(ASN1ObjectIdentifier([1, 2, 840, 113549, 1, 9, 3])) // ContentType
        ..add(ASN1Set()..add(ASN1ObjectIdentifier([1, 2, 840, 113549, 1, 7, 1]))), // Data
      ASN1Sequence()
        ..add(ASN1ObjectIdentifier([1, 2, 840, 113549, 1, 9, 5])) // SigningTime
        ..add(ASN1Set()..add(ASN1UtcTime(signTime))),
      ASN1Sequence()
        ..add(ASN1ObjectIdentifier([1, 2, 840, 113549, 1, 9, 4])) // MessageDigest
        ..add(ASN1Set()..add(ASN1OctetString(base64.decode(digest)))),
    ];
    root.add(ASN1OctetString(authenticatedAttributes.map((e) => e.encodedBytes).expand((x) => x).toList(), tag: CONTEXT_SPECIFIC_TYPE));
    // Signature Algorithm
    root.add(
      ASN1Sequence()
        ..add(signatureIdentifier)
        ..add(ASN1Null()),
    );
    // Signature
    if (signature != null) root.add(ASN1OctetString(base64.decode(signature!)));

    return root;
  }

  String get content => base64.encode(sequence.encodedBytes);
}
