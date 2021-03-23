import 'package:crypt_signature/models/storage.dart';
import 'package:uuid/uuid.dart';

class Certificate {
  static final Storage<Certificate> storage =
      new Storage<Certificate>(Certificate.fromJson);

  final String uuid;
  final String certificate;
  final String alias;
  final String issuerDN;
  final String notAfterDate;
  final String serialNumber;
  final String algorithm;

  Certificate(
      {this.uuid,
      this.certificate,
      this.alias,
      this.issuerDN,
      this.notAfterDate,
      this.serialNumber,
      this.algorithm});

  Map<String, dynamic> toJson() => {
        'uuid': uuid,
        'certificate': certificate,
        'alias': alias,
        'issuerDN': issuerDN,
        'notAfterDate': notAfterDate,
        'serialNumber': serialNumber,
        'algorithm': algorithm
      };

  static Certificate fromJson(Map<String, dynamic> json) => Certificate(
      uuid: json["uuid"] ?? Uuid().v4(),
      certificate: json["certificate"] as String,
      alias: json['alias'] as String,
      issuerDN: json['issuerDN'] as String,
      notAfterDate: json['notAfterDate'] as String,
      serialNumber: json['serialNumber'] as String,
      algorithm: json['algorithm'] as String);

  @override
  // ignore: hash_and_equals
  bool operator ==(other) {
    return (other is Certificate) &&
        other.certificate == certificate &&
        other.serialNumber == serialNumber &&
        other.issuerDN == issuerDN;
  }
}
