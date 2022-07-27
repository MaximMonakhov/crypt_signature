import 'package:asn1lib/asn1lib.dart';
import 'package:crypt_signature/utils/X509Certificate/objectidentifier.dart';
import 'package:crypto_keys/crypto_keys.dart' hide AlgorithmIdentifier;

RsaPublicKey rsaPublicKeyFromAsn1(ASN1Sequence sequence) {
  var modulus = (sequence.elements[0] as ASN1Integer).valueAsBigInteger;
  var exponent = (sequence.elements[1] as ASN1Integer).valueAsBigInteger;
  return RsaPublicKey(modulus: modulus, exponent: exponent);
}

Identifier _lengthToCurve(int l) {
  switch (l) {
    case 32:
      return curves.p256;
    case 48:
      return curves.p384;
    case 66:
      return curves.p521;
  }
  throw UnsupportedError('No matching curve for length $l');
}

EcPublicKey ecPublicKeyFromAsn1(ASN1BitString bitString, {Identifier curve}) {
  var bytes = bitString.contentBytes();
  var compression = bytes[0];
  switch (compression) {
    case 4:
      // uncompressed
      var l = (bytes.length - 1) ~/ 2;
      var x = toBigInt(bytes.sublist(1, l + 1));
      var y = toBigInt(bytes.sublist(l + 1));
      return EcPublicKey(xCoordinate: x, yCoordinate: y, curve: curve ?? _lengthToCurve(l));
    case 2:
    case 3:
      throw UnsupportedError('Compressed key not supported');
    default:
      throw ArgumentError('Invalid compression value $compression');
  }
}

String keyToString(Key key, [String prefix = '']) {
  if (key is RsaPublicKey) {
    var buffer = StringBuffer();
    var l = key.modulus.bitLength;
    buffer.writeln('${prefix}Modulus ($l bit):');
    buffer.writeln(toHexString(key.modulus, '$prefix\t'));
    buffer.writeln('${prefix}Exponent: ${key.exponent}');
    return buffer.toString();
  }
  return '$prefix$key';
}

ASN1BitString keyToAsn1(Key key) {
  var s = ASN1Sequence();
  if (key is RsaPublicKey) {
    s
      ..add(ASN1Integer(key.modulus))
      ..add(ASN1Integer(key.exponent));
  }
  return ASN1BitString(s.encodedBytes);
}

ASN1BitString keyPairToAsn1(KeyPair keyPair) {
  var s = ASN1Sequence();

  var key = keyPair.privateKey as RsaPrivateKey;
  var publicKey = keyPair.publicKey as RsaPublicKey;
  var pSub1 = key.firstPrimeFactor - BigInt.one;
  var qSub1 = key.secondPrimeFactor - BigInt.one;
  var exponent1 = key.privateExponent.remainder(pSub1);
  var exponent2 = key.privateExponent.remainder(qSub1);
  var coefficient = key.secondPrimeFactor.modInverse(key.firstPrimeFactor);

  s
    ..add(fromDart(0)) // version
    ..add(fromDart(key.modulus))
    ..add(fromDart(publicKey.exponent))
    ..add(fromDart(key.privateExponent))
    ..add(fromDart(key.firstPrimeFactor))
    ..add(fromDart(key.secondPrimeFactor))
    ..add(fromDart(exponent1))
    ..add(fromDart(exponent2))
    ..add(fromDart(coefficient));

  return ASN1BitString(s.encodedBytes);
}

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

T toDart<T>(ASN1Object obj) {
  if (obj is ASN1Null) return null;
  if (obj is ASN1Sequence) return obj.elements.map(toDart).toList() as T;
  if (obj is ASN1Set) return obj.elements.map(toDart).toSet() as T;
  if (obj is ASN1Integer) return obj.valueAsBigInteger as T;
  if (obj is ASN1ObjectIdentifier) return ObjectIdentifier.fromAsn1(obj) as T;
  if (obj is ASN1BitString) return obj.stringValue as T;
  if (obj is ASN1Boolean) return obj.booleanValue as T;
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

String toHexString(BigInt v, [String prefix = '', int bytesPerLine = 15]) {
  var str = v.toRadixString(16);
  if (str.length % 2 != 0) {
    str = '0$str';
  }
  var buffer = StringBuffer();
  for (var i = 0; i < str.length; i += bytesPerLine * 2) {
    var l = Iterable.generate(str.length - i < bytesPerLine * 2 ? (str.length - i) ~/ 2 : bytesPerLine, (j) => str.substring(i + j * 2, i + j * 2 + 2));
    var s = l.join(':');
    buffer.writeln('$prefix$s${str.length - i <= bytesPerLine * 2 ? '' : ':'}');
  }
  return buffer.toString();
}

BigInt toBigInt(List<int> bytes) => bytes.fold(BigInt.zero, (a, b) => a * BigInt.from(256) + BigInt.from(b));
