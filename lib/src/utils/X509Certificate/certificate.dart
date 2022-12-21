import 'package:asn1lib/asn1lib.dart';
import 'package:crypt_signature/src/utils/X509Certificate/util.dart';
import 'package:crypt_signature/src/utils/X509Certificate/x509_base.dart';
import 'package:crypto_keys/crypto_keys.dart' hide AlgorithmIdentifier;

/// A Certificate.
abstract class Certificate {
  /// The public key from this certificate.
  PublicKey? get publicKey;
}

/// A X.509 Certificate
class X509Certificate implements Certificate {
  /// The to-be-signed certificate
  final TbsCertificate tbsCertificate;

  ///
  final AlgorithmIdentifier signatureAlgorithm;
  final List<int>? signatureValue;

  @override
  PublicKey? get publicKey => tbsCertificate.subjectPublicKeyInfo.subjectPublicKey;

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

  @override
  String toString([String prefix = '']) {
    var buffer = StringBuffer();
    buffer.writeln('Certificate: ');
    buffer.writeln('\tData:');
    buffer.writeln(tbsCertificate.toString('\t\t'));
    buffer.writeln('\tSignature Algorithm: $signatureAlgorithm');
    buffer.writeln(toHexString(toBigInt(signatureValue!), '$prefix\t\t', 18));
    return buffer.toString();
  }
}

/// An unsigned (To-Be-Signed) certificate.
class TbsCertificate {
  /// The version number of the certificate.
  final int version;

  /// The serial number of the certificate.
  final BigInt serialNumber;

  /// The signature of the certificate.
  final AlgorithmIdentifier signature;

  /// The issuer of the certificate.
  final Name issuer;

  /// The time interval for which this certificate is valid.
  final Validity validity;

  /// The subject of the certificate.
  final Name subject;

  final SubjectPublicKeyInfo subjectPublicKeyInfo;

  const TbsCertificate({
    required this.version,
    required this.serialNumber,
    required this.signature,
    required this.issuer,
    required this.validity,
    required this.subject,
    required this.subjectPublicKeyInfo,
  });

  factory TbsCertificate.fromAsn1(ASN1Sequence sequence) {
    List<ASN1Object> elements = sequence.elements;
    var version = 1;
    if (elements.first.tag == 0xa0) {
      var e = ASN1Parser(elements.first.valueBytes()).nextObject() as ASN1Integer;
      version = e.valueAsBigInteger!.toInt() + 1;
      elements = elements.skip(1).toList();
    }

    return TbsCertificate(
      version: version,
      serialNumber: (elements[0] as ASN1Integer).valueAsBigInteger!,
      signature: AlgorithmIdentifier.fromAsn1(elements[1] as ASN1Sequence),
      issuer: Name.fromAsn1(elements[2] as ASN1Sequence),
      validity: Validity.fromAsn1(elements[3] as ASN1Sequence),
      subject: Name.fromAsn1(elements[4] as ASN1Sequence),
      subjectPublicKeyInfo: SubjectPublicKeyInfo.fromAsn1(elements[5] as ASN1Sequence),
    );
  }

  @override
  String toString([String prefix = '']) {
    var buffer = StringBuffer();
    buffer.writeln('${prefix}Version: $version');
    buffer.writeln('${prefix}Serial Number: $serialNumber');
    buffer.writeln('${prefix}Signature Algorithm: $signature');
    buffer.writeln('${prefix}Issuer: $issuer');
    buffer.writeln('${prefix}Validity:');
    buffer.writeln(validity.toString('$prefix\t'));
    buffer.writeln('${prefix}Subject: $subject');
    buffer.writeln('${prefix}Subject Public Key Info:');
    buffer.writeln(subjectPublicKeyInfo.toString('$prefix\t'));
    return buffer.toString();
  }
}
