import 'dart:convert';
import 'dart:typed_data';

import 'package:asn1lib/asn1lib.dart';
import 'package:crypt_signature/src/utils/X509Certificate/dart_convertes.dart';
import 'package:crypt_signature/src/utils/X509Certificate/identifiers/algorithm_identifier.dart';
import 'package:crypt_signature/src/utils/X509Certificate/tbs_certificate.dart';

/// A X.509 Certificate
class X509Certificate {
  final TbsCertificate tbsCertificate;
  final AlgorithmIdentifier signatureAlgorithm;
  final List<int>? signatureValue;

  const X509Certificate(this.tbsCertificate, this.signatureAlgorithm, this.signatureValue);

  /// Creates a certificate from an [ASN1Sequence].
  ///
  /// The ASN.1 definition is:
  ///
  ///   Certificate  ::=  SEQUENCE  {
  ///     tbsCertificate       TBSCertificate,
  ///     signatureAlgorithm   AlgorithmIdentifier,
  ///     signatureValue       BIT STRING  }
  factory X509Certificate.fromAsn1(ASN1Sequence sequence) {
    final algorithm = AlgorithmIdentifier.fromAsn1(sequence.elements[1] as ASN1Sequence);
    return X509Certificate(TbsCertificate.fromAsn1(sequence.elements[0] as ASN1Sequence), algorithm, toDart(sequence.elements[2]));
  }

  factory X509Certificate.fromPem(String pem) {
    var lines = pem.split('\n').map((line) => line.trim()).where((line) => line.isNotEmpty).toList();

    final re = RegExp(r'^-----BEGIN (.+)-----$');
    late Uint8List bytes;
    String? type;

    var i = 0;
    var l = lines[i];
    var match = re.firstMatch(l);
    if (match == null) {
      throw ArgumentError(
        'The given string does not have the correct '
        'begin marker expected in a PEM file.',
      );
    }
    type = match.group(1);

    var startI = ++i;
    while (i < lines.length && lines[i] != '-----END $type-----') {
      i++;
    }
    if (i >= lines.length) {
      throw ArgumentError(
        'The given string does not have the correct '
        'end marker expected in a PEM file.',
      );
    }

    var b = lines.sublist(startI, i).join();
    bytes = base64.decode(b);

    var p = ASN1Parser(bytes);
    var o = p.nextObject();
    if (o is! ASN1Sequence) {
      throw FormatException('Expected SEQUENCE, got ${o.runtimeType}');
    }
    ASN1Object s = o;

    switch (type) {
      case 'CERTIFICATE':
        return X509Certificate.fromAsn1(s as ASN1Sequence);
    }
    throw const FormatException('Could not parse PEM');
  }
}
