import 'package:asn1lib/asn1lib.dart';
import 'package:crypt_signature/utils/X509Certificate/util.dart';
import 'package:crypt_signature/utils/X509Certificate/x509_base.dart';
import 'package:crypto_keys/crypto_keys.dart' hide AlgorithmIdentifier;

/// A Certificate.
abstract class Certificate {
  /// The public key from this certificate.
  PublicKey get publicKey;
}

/// A X.509 Certificate
class X509Certificate implements Certificate {
  /// The to-be-signed certificate
  final TbsCertificate tbsCertificate;

  ///
  final AlgorithmIdentifier signatureAlgorithm;
  final List<int> signatureValue;

  @override
  PublicKey get publicKey => tbsCertificate.subjectPublicKeyInfo.subjectPublicKey;

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

  ASN1Sequence toAsn1() {
    return ASN1Sequence()
      ..add(tbsCertificate.toAsn1())
      ..add(signatureAlgorithm.toAsn1())
      ..add(fromDart(signatureValue));
  }

  @override
  String toString([String prefix = '']) {
    var buffer = StringBuffer();
    buffer.writeln('Certificate: ');
    buffer.writeln('\tData:');
    buffer.writeln(tbsCertificate.toString('\t\t'));
    buffer.writeln('\tSignature Algorithm: $signatureAlgorithm');
    buffer.writeln(toHexString(toBigInt(signatureValue), '$prefix\t\t', 18));
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

  /// The issuer unique id.
  final List<int> issuerUniqueID;

  /// The subject unique id.
  final List<int> subjectUniqueID;

  const TbsCertificate({
    this.version,
    this.serialNumber,
    this.signature,
    this.issuer,
    this.validity,
    this.subject,
    this.subjectPublicKeyInfo,
    this.issuerUniqueID,
    this.subjectUniqueID,
  });

  factory TbsCertificate.fromAsn1(ASN1Sequence sequence) {
    List<ASN1Object> elements = sequence.elements;
    var version = 1;
    if (elements.first.tag == 0xa0) {
      var e = ASN1Parser(elements.first.valueBytes()).nextObject() as ASN1Integer;
      version = e.valueAsBigInteger.toInt() + 1;
      elements = elements.skip(1).toList();
    }

    return TbsCertificate(
      version: version,
      serialNumber: (elements[0] as ASN1Integer).valueAsBigInteger,
      signature: AlgorithmIdentifier.fromAsn1(elements[1] as ASN1Sequence),
      issuer: Name.fromAsn1(elements[2] as ASN1Sequence),
      validity: Validity.fromAsn1(elements[3] as ASN1Sequence),
      subject: Name.fromAsn1(elements[4] as ASN1Sequence),
      subjectPublicKeyInfo: SubjectPublicKeyInfo.fromAsn1(elements[5] as ASN1Sequence),
    );
  }

  ASN1Sequence toAsn1() {
    var seq = ASN1Sequence();

    if (version != 1) {
      var v = ASN1Integer(BigInt.from(version - 1));
      var o = ASN1Object.preEncoded(0xa0, v.encodedBytes);
      var b = o.encodedBytes..setRange(o.encodedBytes.length - v.encodedBytes.length, o.encodedBytes.length, v.encodedBytes);
      o = ASN1Object.fromBytes(b);
      seq.add(o);
    }
    seq
      ..add(fromDart(serialNumber))
      ..add(signature.toAsn1())
      ..add(issuer.toAsn1())
      ..add(validity.toAsn1())
      ..add(subject.toAsn1())
      ..add(subjectPublicKeyInfo.toAsn1());
    if (version > 1) {
      if (issuerUniqueID != null) {
        // TODO: Изменения в пакете
        // var iuid = ASN1BitString.fromBytes(issuerUniqueID);
        //ASN1Object.preEncoded(tag, valBytes)
      }
    }
    return seq;
  }

  @override
  String toString([String prefix = '']) {
    var buffer = StringBuffer();
    buffer.writeln('${prefix}Version: $version');
    buffer.writeln('${prefix}Serial Number: $serialNumber');
    buffer.writeln('${prefix}Signature Algorithm: $signature');
    buffer.writeln('${prefix}Issuer: $issuer');
    buffer.writeln('${prefix}Validity:');
    buffer.writeln(validity?.toString('$prefix\t') ?? '');
    buffer.writeln('${prefix}Subject: $subject');
    buffer.writeln('${prefix}Subject Public Key Info:');
    buffer.writeln(subjectPublicKeyInfo?.toString('$prefix\t') ?? '');
    return buffer.toString();
  }
}
