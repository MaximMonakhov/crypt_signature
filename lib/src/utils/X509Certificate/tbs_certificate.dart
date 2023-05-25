import 'package:asn1lib/asn1lib.dart';
import 'package:crypt_signature/src/utils/X509Certificate/identifiers/algorithm_identifier.dart';
import 'package:crypt_signature/src/utils/X509Certificate/identifiers/name_identifier.dart';
import 'package:crypt_signature/src/utils/X509Certificate/identifiers/subject_public_key_info.dart';
import 'package:crypt_signature/src/utils/X509Certificate/identifiers/validity_identifier.dart';

/// An unsigned (To-Be-Signed) certificate.
class TbsCertificate {
  /// The version number of the certificate.
  final int version;

  /// The serial number of the certificate.
  final BigInt serialNumber;

  /// The signature of the certificate.
  final AlgorithmIdentifier signature;

  /// The issuer of the certificate.
  final NameIdentifier issuer;

  /// The time interval for which this certificate is valid.
  final ValidityIdentifier validity;

  /// The subject of the certificate.
  final NameIdentifier subject;

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
      issuer: NameIdentifier.fromAsn1(elements[2] as ASN1Sequence),
      validity: ValidityIdentifier.fromAsn1(elements[3] as ASN1Sequence),
      subject: NameIdentifier.fromAsn1(elements[4] as ASN1Sequence),
      subjectPublicKeyInfo: SubjectPublicKeyInfo.fromAsn1(elements[5] as ASN1Sequence),
    );
  }
}
