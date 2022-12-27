import 'package:flutter_c14n/flutter_c14n.dart';

enum CanonicalizationType {
  canonicalXml,
  canonicalXmlWithComments,
  canonicalXml11,
  canonicalXml11WithComments,
  exclusiveXmlC14n,
  exclusiveXmlC14nWithComments
}

C14nType canonicalizationToC14n(CanonicalizationType type) {
  final Iterable<C14nType> targetEnumValues = C14nType.values.where((e) => e.name == type.name);
  if(targetEnumValues.isEmpty) throw Exception('Illegal type');
  return targetEnumValues.first;
}
