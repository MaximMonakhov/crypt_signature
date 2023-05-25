import 'package:asn1lib/asn1lib.dart';
import 'package:crypt_signature/src/utils/X509Certificate/identifiers/object_identifier.dart';

ASN1Object fromDart(dynamic obj) {
  if (obj == null) return ASN1Null();
  if (obj is List<int>) return ASN1BitString(obj);
  if (obj is List) {
    var s = ASN1Sequence();
    for (final v in obj) {
      s.add(fromDart(v));
    }
    return s;
  }
  if (obj is Set) {
    var s = ASN1Set();
    for (final v in obj) {
      s.add(fromDart(v));
    }
    return s;
  }
  if (obj is BigInt) return ASN1Integer(obj);
  if (obj is int) return ASN1Integer(BigInt.from(obj));
  if (obj is ObjectIdentifier) return obj.toAsn1();
  if (obj is bool) return ASN1Boolean(obj);
  if (obj is String) return ASN1PrintableString(obj);
  if (obj is DateTime) return ASN1UtcTime(obj);

  throw ArgumentError.value(obj, 'obj', 'cannot be encoded as ASN1Object');
}

T? toDart<T>(ASN1Object obj) {
  if (obj is ASN1Null) return null;
  if (obj is ASN1Sequence) return obj.elements.map(toDart).toList() as T;
  if (obj is ASN1Set) return obj.elements.map(toDart).toSet() as T;
  if (obj is ASN1Integer) return obj.valueAsBigInteger as T?;
  if (obj is ASN1ObjectIdentifier) return ObjectIdentifier.fromAsn1(obj) as T;
  if (obj is ASN1BitString) return obj.stringValue as T;
  if (obj is ASN1Boolean) return obj.booleanValue as T?;
  if (obj is ASN1OctetString) return obj.stringValue as T;
  if (obj is ASN1PrintableString) return obj.stringValue as T;
  if (obj is ASN1UtcTime) return obj.dateTimeValue as T;
  if (obj is ASN1IA5String) return obj.stringValue as T;
  if (obj is ASN1UTF8String) return obj.utf8StringValue as T;
  if (obj is ASN1NumericString) return obj.stringValue as T;
  switch (obj.tag) {
    case 0xa0:
      return toDart(ASN1Parser(obj.valueBytes()).nextObject());
    case 0x86:
      return null;
  }
  return null;
}
