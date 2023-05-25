import 'package:asn1lib/asn1lib.dart';
import 'package:crypt_signature/src/utils/X509Certificate/dart_converters.dart';

class ValidityIdentifier {
  final DateTime? notBefore;
  final DateTime? notAfter;

  ValidityIdentifier({required this.notBefore, required this.notAfter});

  factory ValidityIdentifier.fromAsn1(ASN1Sequence sequence) => ValidityIdentifier(
        notBefore: toDart(sequence.elements[0]) as DateTime?,
        notAfter: toDart(sequence.elements[1]) as DateTime?,
      );

  ASN1Sequence toAsn1() => ASN1Sequence()
    ..add(fromDart(notBefore))
    ..add(fromDart(notAfter));

  @override
  String toString([String prefix = '']) {
    var buffer = StringBuffer();
    buffer.writeln('${prefix}Not Before: $notBefore');
    buffer.writeln('${prefix}Not After: $notAfter');
    return buffer.toString();
  }
}
