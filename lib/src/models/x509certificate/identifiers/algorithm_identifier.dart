import 'package:asn1lib/asn1lib.dart';
import 'package:crypt_signature/src/models/x509certificate/identifiers/object_identifier.dart';
import 'package:crypt_signature/src/utils/dart_converters.dart';

class AlgorithmIdentifier {
  final ObjectIdentifier? algorithm;
  // ignore: type_annotate_public_apis, prefer_typing_uninitialized_variables
  final parameters;

  AlgorithmIdentifier(this.algorithm, this.parameters);

  /// AlgorithmIdentifier  ::=  SEQUENCE  {
  ///   algorithm               OBJECT IDENTIFIER,
  ///   parameters              ANY DEFINED BY algorithm OPTIONAL  }
  ///                             -- contains a value of the type
  ///                             -- registered for use with the
  ///                             -- algorithm object identifier value
  factory AlgorithmIdentifier.fromAsn1(ASN1Sequence sequence) {
    var algorithm = toDart(sequence.elements[0]);
    var parameters = sequence.elements.length > 1 ? toDart(sequence.elements[1]) : null;
    return AlgorithmIdentifier(algorithm as ObjectIdentifier?, parameters);
  }

  ASN1Sequence toAsn1() {
    var seq = ASN1Sequence()..add(fromDart(algorithm));
    seq.add(fromDart(parameters));
    return seq;
  }

  @override
  String toString() => "$algorithm${parameters == null ? "" : "($parameters)"}";
}
