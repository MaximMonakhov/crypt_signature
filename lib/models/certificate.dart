import 'package:crypt_signature/models/algorithm.dart';
import 'package:crypt_signature/models/storage.dart';
import 'package:crypt_signature/utils/X509Certificate/certificate.dart' as x509_certificate;
import 'package:crypt_signature/utils/X509Certificate/x509_base.dart' as x509_base;
import 'package:intl/intl.dart';
import 'package:uuid/uuid.dart';

class Certificate {
  static const String PEM_START_STRING = "-----BEGIN CERTIFICATE-----\n";
  static const String PEM_END_STRING = "\n-----END CERTIFICATE-----\n";

  static final Storage<Certificate> storage = Storage<Certificate>(parser: Certificate.fromJson);

  final String uuid;
  final String certificate;
  final String alias;
  final String subjectDN;
  final String notAfterDate;
  final String serialNumber;
  final Algorithm algorithm;
  final x509_certificate.X509Certificate x509certificate;

  String parameterMap;
  String certificateDescription;

  Certificate({
    this.uuid,
    this.certificate,
    this.alias,
    this.subjectDN,
    this.notAfterDate,
    this.serialNumber,
    this.algorithm,
    this.parameterMap,
    this.certificateDescription,
    this.x509certificate,
  });

  Map<String, dynamic> toJson() => {
        'uuid': uuid,
        'certificate': certificate,
        'alias': alias,
        'subjectDN': subjectDN,
        'notAfterDate': notAfterDate,
        'serialNumber': serialNumber,
        'algorithm': algorithm,
        'parameterMap': parameterMap,
        'certificateDescription': certificateDescription
      };

  void setParams() {
    parameterMap = getParameterMap();
    certificateDescription = getCertificateDescription();
  }

  static Certificate fromJson(Map json) => Certificate(
        uuid: json["uuid"] as String ?? const Uuid().v4(),
        certificate: json["certificate"] as String,
        alias: json['alias'] as String,
        subjectDN: json['subjectDN'] as String,
        notAfterDate: json['notAfterDate'] as String,
        serialNumber: json['serialNumber'] as String,
        algorithm: Algorithm.fromJson(json['algorithm'] as Map),
        parameterMap: json['parameterMap'] as String,
        certificateDescription: json['certificateDescription'] as String,
      );

  static Certificate fromBase64(Map data) {
    final String pem = PEM_START_STRING + (data["certificate"] as String) + PEM_END_STRING;
    final x509_certificate.X509Certificate cert = x509_base.parsePem(pem).first as x509_certificate.X509Certificate;

    String publicKeyOID = cert.tbsCertificate.subjectPublicKeyInfo.algorithm.algorithm.name;
    Algorithm algorithm = Algorithm.findAlgorithmByPublicKeyOID(publicKeyOID);

    String notAfterDate = DateFormat('HH:mm dd-MM-yyyy').format(cert.tbsCertificate.validity.notAfter);

    Certificate certificate = Certificate(
      uuid: const Uuid().v4(),
      certificate: data["certificate"] as String,
      alias: data["alias"] as String,
      subjectDN: cert.tbsCertificate.subject.toString(),
      notAfterDate: notAfterDate,
      serialNumber: cert.tbsCertificate.serialNumber.toRadixString(16),
      algorithm: algorithm,
      x509certificate: cert,
    );

    certificate.setParams();

    return certificate;
  }

  @override
  // ignore: hash_and_equals
  bool operator ==(dynamic other) {
    return (other is Certificate) && other.certificate == certificate && other.serialNumber == serialNumber;
  }

  String getParameterMap() {
    const String PARAMETER_SEPARATOR = "&";
    StringBuffer stringBuffer = StringBuffer();

    stringBuffer.write(
      "validFromDate=${x509certificate.tbsCertificate.validity.notBefore}$PARAMETER_SEPARATOR",
    );
    stringBuffer.write(
      "validToDate=${x509certificate.tbsCertificate.validity.notAfter}$PARAMETER_SEPARATOR",
    );
    stringBuffer.write(
      "issuer=${x509certificate.tbsCertificate.issuer}$PARAMETER_SEPARATOR",
    );
    stringBuffer.write(
      "subject=${x509certificate.tbsCertificate.subject}$PARAMETER_SEPARATOR",
    );
    stringBuffer.write(
      "subjectInfo=${x509certificate.tbsCertificate.subject}$PARAMETER_SEPARATOR",
    );
    stringBuffer.write(
      "issuerInfo=${x509certificate.tbsCertificate.issuer}$PARAMETER_SEPARATOR",
    );
    stringBuffer.write(
      "serialNumber=${x509certificate.tbsCertificate.serialNumber.toRadixString(16)}$PARAMETER_SEPARATOR",
    );
    stringBuffer.write(
      "signAlgoritm[name]=${algorithm.name}$PARAMETER_SEPARATOR",
    );
    stringBuffer.write(
      "signAlgoritm[oid]=${algorithm.signatureOID}$PARAMETER_SEPARATOR",
    );
    stringBuffer.write(
      "hashAlgoritm[alias]=${algorithm.hashOID}",
    );

    return stringBuffer.toString();
  }

  String getCertificateDescription() {
    const String DESCRIPTION_SEPARATOR = "\n";
    StringBuffer stringBuffer = StringBuffer();

    stringBuffer.write(
      "Владелец: ${x509certificate.tbsCertificate.subject}$DESCRIPTION_SEPARATOR",
    );
    stringBuffer.write(
      "Серийный номер: ${x509certificate.tbsCertificate.serialNumber.toRadixString(16)}$DESCRIPTION_SEPARATOR",
    );
    stringBuffer.write(
      "Издатель: ${x509certificate.tbsCertificate.issuer}$DESCRIPTION_SEPARATOR",
    );
    stringBuffer.write(
      "Алгоритм подписи:${algorithm.name}$DESCRIPTION_SEPARATOR",
    );
    stringBuffer.write(
      "Действует с: ${x509certificate.tbsCertificate.validity.notBefore}$DESCRIPTION_SEPARATOR",
    );
    stringBuffer.write(
      "Действует по: ${x509certificate.tbsCertificate.validity.notAfter}",
    );

    return stringBuffer.toString();
  }
}
