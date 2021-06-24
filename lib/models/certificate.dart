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
  final String parameterMap;
  final String certificateDescription;

  Certificate(
      {this.uuid,
      this.certificate,
      this.alias,
      this.issuerDN,
      this.notAfterDate,
      this.serialNumber,
      this.algorithm,
      this.parameterMap,
      this.certificateDescription});

  Map<String, dynamic> toJson() => {
        'uuid': uuid,
        'certificate': certificate,
        'alias': alias,
        'issuerDN': issuerDN,
        'notAfterDate': notAfterDate,
        'serialNumber': serialNumber,
        'algorithm': algorithm,
        'parameterMap': parameterMap,
        'certificateDescription': certificateDescription
      };

  static Certificate fromJson(Map<String, dynamic> json) => Certificate(
      uuid: json["uuid"] ?? Uuid().v4(),
      certificate: json["certificate"] as String,
      alias: json['alias'] as String,
      issuerDN: json['issuerDN'] as String,
      notAfterDate: json['notAfterDate'] as String,
      serialNumber: json['serialNumber'] as String,
      algorithm: json['algorithm'] as String,
      parameterMap: json['parameterMap'] as String,
      certificateDescription: json['certificateDescription'] as String);

  @override
  // ignore: hash_and_equals
  bool operator ==(other) {
    return (other is Certificate) &&
        other.certificate == certificate &&
        other.serialNumber == serialNumber &&
        other.issuerDN == issuerDN;
  }
}
