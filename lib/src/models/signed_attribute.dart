import 'dart:convert';

import 'package:asn1lib/asn1lib.dart';
import 'package:crypt_signature/src/models/certificate.dart';
import 'package:crypt_signature/src/models/pkcs7.dart';

class SignedAttribute {
  final List<ASN1Sequence> attributes;

  SignedAttribute(
    Certificate certificate,
    ASN1ObjectIdentifier digestIdentifier, {
    required String digest,
    required String certificateDigest,
    DateTime? signTime,
  }) : attributes = [
          ASN1Sequence()
            ..add(ASN1ObjectIdentifier([1, 2, 840, 113549, 1, 9, 3])) // ContentType
            ..add(ASN1Set()..add(ASN1ObjectIdentifier([1, 2, 840, 113549, 1, 7, 1]))), // Data
          ASN1Sequence()
            ..add(ASN1ObjectIdentifier([1, 2, 840, 113549, 1, 9, 5])) // SigningTime
            ..add(ASN1Set()..add(ASN1UtcTime(signTime ?? DateTime.now().toUtc()))),
          ASN1Sequence()
            ..add(ASN1ObjectIdentifier([1, 2, 840, 113549, 1, 9, 4])) // MessageDigest
            ..add(ASN1Set()..add(ASN1OctetString(base64.decode(digest)))),
          ASN1Sequence()
            ..add(ASN1ObjectIdentifier([1, 2, 840, 113549, 1, 9, 16, 2, 47])) // Signed Certificate
            ..add(
              ASN1Set()
                ..add(
                  ASN1Sequence()
                    ..add(
                      ASN1Sequence()
                        ..add(
                          ASN1Sequence()
                            ..add(
                              ASN1Sequence()
                                ..add(digestIdentifier)
                                ..add(ASN1Null()),
                            )
                            ..add(ASN1OctetString(base64.decode(certificateDigest)))
                            ..add(
                              ASN1Sequence()
                                ..add(
                                  ASN1Sequence()
                                    ..add(
                                      ASN1OctetString(
                                        certificate.x509certificate.tbsCertificate.issuer.encodedBytes,
                                        tag: 0xA4,
                                      ),
                                    ),
                                )
                                ..add(ASN1Integer(BigInt.parse(certificate.serialNumber, radix: 16))),
                            ),
                        ),
                    ),
                ),
            ),
        ];

  ASN1OctetString get sequence => ASN1OctetString(
        attributes.map((e) => e.encodedBytes).expand((x) => x).toList(),
        tag: CONTEXT_SPECIFIC_TYPE,
      );

  /// Атрибуты подписи должны быть подписаны как Set, а добавлены к PKCS7 как Context Specific Octet String
  String get message => base64.encode(attributes.fold(ASN1Set(), (set, e) => set..add(e)).encodedBytes);
}
