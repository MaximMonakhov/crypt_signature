import 'package:asn1lib/asn1lib.dart';

class Algorithm {
  static const List<Algorithm> algorithms = [
    Algorithm("ГОСТ Р 34.10-2001", "1.2.643.2.2.9", "1.2.643.2.2.19", "1.2.643.2.2.3"),
    Algorithm("ГОСТ Р 34.10-2012", "1.2.643.7.1.1.2.2", "1.2.643.7.1.1.1.1", "1.2.643.7.1.1.3.2"),
    Algorithm("ГОСТ Р 34.10-2012 Strong", "1.2.643.7.1.1.2.3", "1.2.643.7.1.1.1.2", "1.2.643.7.1.1.3.3"),
    Algorithm("Неизвестен", "Неизвестен", "Неизвестен", "Неизвестен"),
  ];

  final String name;
  final String hashOID;
  final String publicKeyOID;
  final String signatureOID;

  const Algorithm(this.name, this.hashOID, this.publicKeyOID, this.signatureOID);

  static Algorithm findAlgorithmByPublicKeyOID(String? publicKeyOID) {
    if (publicKeyOID == null) return algorithms.last;

    final String formatedPublicKeyOID = formatOID(publicKeyOID);
    return algorithms.firstWhere((algorithm) => algorithm.publicKeyOID == formatedPublicKeyOID, orElse: () => algorithms.last);
  }

  static String formatOID(String rawOID) => rawOID.replaceAll("[", "").replaceAll("]", "").replaceAll(" ", "").replaceAll(",", ".");

  Map<String, String> toJson() => {
        'name': name,
        'hashOID': hashOID,
        'publicKeyOID': publicKeyOID,
        'signatureOID': signatureOID,
      };

  ASN1ObjectIdentifier toAsn(String value) => ASN1ObjectIdentifier(value.split(".").map((e) => int.parse(e)).toList());

  Algorithm get unknown => algorithms.last;

  Algorithm.fromJson(Map<String, dynamic> json)
      : name = json['name'] as String,
        hashOID = json['hashOID'] as String,
        publicKeyOID = json['publicKeyOID'] as String,
        signatureOID = json['signatureOID'] as String;

  @override
  int get hashCode => Object.hash(name, hashOID, publicKeyOID, signatureOID);

  @override
  bool operator ==(Object other) => other is Algorithm && other.hashCode == hashCode;

  @override
  String toString() => name;
}
