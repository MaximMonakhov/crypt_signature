import 'package:asn1lib/asn1lib.dart';
import 'package:crypt_signature/src/models/x509certificate/identifiers/object_identifier.dart';
import 'package:crypt_signature/src/utils/dart_converters.dart';

class NameIdentifier {
  final List<Map<ObjectIdentifier?, dynamic>> names;

  const NameIdentifier(this.names);

  factory NameIdentifier.fromAsn1(ASN1Sequence sequence) => NameIdentifier(
        sequence.elements
            .map(
              (ASN1Object set) => <ObjectIdentifier?, dynamic>{
                for (var p in (set as ASN1Set).elements) toDart((p as ASN1Sequence).elements[0]) as ObjectIdentifier?: toDart(p.elements[1])
              },
            )
            .toList(),
      );

  ASN1Sequence toAsn1() {
    var seq = ASN1Sequence();
    for (final n in names) {
      var set = ASN1Set();
      n.forEach((k, v) {
        set.add(
          ASN1Sequence()
            ..add(fromDart(k))
            ..add(fromDart(v)),
        );
      });
      seq.add(set);
    }
    return seq;
  }

  @override
  String toString() => names.map((m) => m.keys.map((k) => '$k=${m[k]}').join(', ')).join(', ');
}
