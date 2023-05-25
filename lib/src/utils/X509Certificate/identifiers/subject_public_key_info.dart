import 'package:asn1lib/asn1lib.dart';
import 'package:crypt_signature/src/utils/X509Certificate/identifiers/algorithm_identifier.dart';

class SubjectPublicKeyInfo {
  final AlgorithmIdentifier algorithm;

  SubjectPublicKeyInfo(this.algorithm);

  factory SubjectPublicKeyInfo.fromAsn1(ASN1Sequence sequence) {
    final algorithm = AlgorithmIdentifier.fromAsn1(sequence.elements[0] as ASN1Sequence);
    return SubjectPublicKeyInfo(algorithm);
  }
}
