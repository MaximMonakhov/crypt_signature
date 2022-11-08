// Copyright (c) 2016, rbellens. All rights reserved. Use of this source code
// is governed by a BSD-style license that can be found in the LICENSE file.

import 'dart:convert';
import 'dart:typed_data';

import 'package:asn1lib/asn1lib.dart';
import 'package:crypt_signature/utils/X509Certificate/certificate.dart';
import 'package:crypt_signature/utils/X509Certificate/objectidentifier.dart';
import 'package:crypt_signature/utils/X509Certificate/util.dart';
import 'package:crypto_keys/crypto_keys.dart';

class Name {
  final List<Map<ObjectIdentifier?, dynamic>> names;

  const Name(this.names);

  factory Name.fromAsn1(ASN1Sequence sequence) {
    return Name(
      sequence.elements.map((ASN1Object set) {
        return <ObjectIdentifier?, dynamic>{
          for (var p in (set as ASN1Set).elements) toDart((p as ASN1Sequence).elements[0]) as ObjectIdentifier?: toDart(p.elements[1])
        };
      }).toList(),
    );
  }

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

class Validity {
  final DateTime? notBefore;
  final DateTime? notAfter;

  Validity({required this.notBefore, required this.notAfter});

  factory Validity.fromAsn1(ASN1Sequence sequence) => Validity(
        notBefore: toDart(sequence.elements[0]) as DateTime?,
        notAfter: toDart(sequence.elements[1]) as DateTime?,
      );

  ASN1Sequence toAsn1() {
    return ASN1Sequence()
      ..add(fromDart(notBefore))
      ..add(fromDart(notAfter));
  }

  @override
  String toString([String prefix = '']) {
    var buffer = StringBuffer();
    buffer.writeln('${prefix}Not Before: $notBefore');
    buffer.writeln('${prefix}Not After: $notAfter');
    return buffer.toString();
  }
}

class SubjectPublicKeyInfo {
  final AlgorithmIdentifier algorithm;
  final PublicKey? subjectPublicKey;

  SubjectPublicKeyInfo(this.algorithm, this.subjectPublicKey);

  factory SubjectPublicKeyInfo.fromAsn1(ASN1Sequence sequence) {
    final algorithm = AlgorithmIdentifier.fromAsn1(sequence.elements[0] as ASN1Sequence);
    return SubjectPublicKeyInfo(algorithm, null);
  }

  @override
  String toString([String prefix = '']) {
    var buffer = StringBuffer();
    buffer.writeln('${prefix}Public Key Algorithm: $algorithm');
    buffer.writeln('${prefix}RSA Public Key:');
    buffer.writeln(keyToString(subjectPublicKey, '$prefix\t'));
    return buffer.toString();
  }

  ASN1Sequence toAsn1() {
    return ASN1Sequence()
      ..add(algorithm.toAsn1())
      ..add(keyToAsn1(subjectPublicKey));
  }
}

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

Object _parseDer(List<int> bytes, String? type) {
  var p = ASN1Parser(bytes as Uint8List);
  var o = p.nextObject();
  if (o is! ASN1Sequence) {
    throw FormatException('Expected SEQUENCE, got ${o.runtimeType}');
  }
  ASN1Object s = o;

  switch (type) {
    case 'CERTIFICATE':
      return X509Certificate.fromAsn1(s as ASN1Sequence);
  }
  throw const FormatException('Could not parse PEM');
}

Iterable parsePem(String pem) sync* {
  var lines = pem.split('\n').map((line) => line.trim()).where((line) => line.isNotEmpty).toList();

  final re = RegExp(r'^-----BEGIN (.+)-----$');
  for (var i = 0; i < lines.length; i++) {
    var l = lines[i];
    var match = re.firstMatch(l);
    if (match == null) {
      throw ArgumentError(
        'The given string does not have the correct '
        'begin marker expected in a PEM file.',
      );
    }
    var type = match.group(1);

    var startI = ++i;
    while (i < lines.length && lines[i] != '-----END $type-----') {
      i++;
    }
    if (i >= lines.length) {
      throw ArgumentError(
        'The given string does not have the correct '
        'end marker expected in a PEM file.',
      );
    }

    var b = lines.sublist(startI, i).join();
    var bytes = base64.decode(b);
    yield _parseDer(bytes, type);
  }
}
