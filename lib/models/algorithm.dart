class Algorithm {
  static List<Algorithm> algorithms = [
    Algorithm(
      name: "ГОСТ Р 34.10-2001",
      hashOID: "1.2.643.2.2.9",
      publicKeyOID: "1.2.643.2.2.19",
      signatureOID: "1.2.643.2.2.3",
    ),
    Algorithm(
      name: "ГОСТ Р 34.10-2012",
      hashOID: "1.2.643.7.1.1.2.2",
      publicKeyOID: "1.2.643.7.1.1.1.1",
      signatureOID: "1.2.643.7.1.1.3.2",
    ),
    Algorithm(
      name: "ГОСТ Р 34.10-2012 Strong",
      hashOID: "1.2.643.7.1.1.2.3",
      publicKeyOID: "1.2.643.7.1.1.1.2",
      signatureOID: "1.2.643.7.1.1.3.3",
    ),
    Algorithm(
      name: "Неизвестен",
      hashOID: "Неизвестен",
      publicKeyOID: "Неизвестен",
      signatureOID: "Неизвестен",
    ),
  ];

  final String name;
  final String hashOID;
  final String publicKeyOID;
  final String signatureOID;

  Algorithm({this.name, this.hashOID, this.publicKeyOID, this.signatureOID});

  static Algorithm findAlgorithmByPublicKeyOID(String publicKeyOID) {
    if (publicKeyOID == null) return algorithms.last;

    String formatedPublicKeyOID = formatOID(publicKeyOID);
    return algorithms.firstWhere((algorithm) => algorithm.publicKeyOID == formatedPublicKeyOID, orElse: () => algorithms.last);
  }

  static String formatOID(String rawOID) => rawOID
      .replaceAll("[", "")
      .replaceAll("]", "")
      .replaceAll(" ", "")
      .replaceAll(",", ".");
  
  Map<String, dynamic> toJson() => {
        'name': name,
        'hashOID': hashOID,
        'publicKeyOID': publicKeyOID,
        'signatureOID': signatureOID,
      };
  
  Algorithm.fromJson(Map<String, dynamic> json)
      : name = json['name'],
        hashOID = json['hashOID'],
        publicKeyOID = json['publicKeyOID'],
        signatureOID = json['signatureOID'];
}