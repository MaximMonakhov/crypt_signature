import 'dart:io' show Platform;
import 'dart:typed_data';

import 'package:asn1lib/asn1lib.dart';
import 'package:crypt_signature/src/models/algorithm.dart';
import 'package:crypt_signature/src/models/x509certificate/identifiers/object_identifier.dart';
import 'package:crypt_signature/src/models/x509certificate/x509_certificate.dart';
import 'package:crypt_signature/src/utils/dart_converters.dart';
import 'package:intl/intl.dart';
import 'package:uuid/uuid.dart';

class Certificate {
  static const String PEM_START_STRING = "-----BEGIN CERTIFICATE-----\n";
  static const String PEM_END_STRING = "\n-----END CERTIFICATE-----\n";

  final String uuid;
  final String certificate;
  final String alias;
  final String subjectDN;
  final String notAfterDate;
  final String serialNumber;
  final Algorithm algorithm;
  final Map<String, dynamic> parameterMap;
  final String certificateDescription;

  String get pem => PEM_START_STRING + certificate + PEM_END_STRING;
  X509Certificate get x509certificate => X509Certificate.fromPem(pem);

  const Certificate({
    required this.uuid,
    required this.certificate,
    required this.alias,
    required this.subjectDN,
    required this.notAfterDate,
    required this.serialNumber,
    required this.algorithm,
    required this.parameterMap,
    required this.certificateDescription,
  });

  String get storageID => Platform.isIOS ? alias : uuid;

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

  factory Certificate.fromJson(Map<String, dynamic> json) => Certificate(
        uuid: json["uuid"] as String? ?? const Uuid().v4(),
        certificate: json["certificate"] as String,
        alias: json['alias'] as String,
        subjectDN: json['subjectDN'] as String,
        notAfterDate: json['notAfterDate'] as String,
        serialNumber: json['serialNumber'] as String,
        algorithm: Algorithm.fromJson(json['algorithm'] as Map<String, dynamic>),
        parameterMap: json['parameterMap'] as Map<String, dynamic>,
        certificateDescription: json['certificateDescription'] as String,
      );

  factory Certificate.fromBase64(Map<String, dynamic> data) {
    final String pem = PEM_START_STRING + (data["certificate"] as String) + PEM_END_STRING;
    final X509Certificate cert = X509Certificate.fromPem(pem);

    String publicKeyOID = cert.tbsCertificate.subjectPublicKeyInfo.algorithm.algorithm!.name!;
    Algorithm algorithm = Algorithm.findAlgorithmByPublicKeyOID(publicKeyOID);

    String notAfterDate = DateFormat('HH:mm dd-MM-yyyy').format(cert.tbsCertificate.validity.notAfter!);
    String serialNumber = parseSerialNumberToHex(cert.tbsCertificate.serialNumber);

    List<String> subjectFields = [];
    for (final ASN1Object element in cert.tbsCertificate.subject.elements) {
      if (element is ASN1Set) {
        final ASN1Object object = element.elements.first;
        dynamic objectValue = toDart(object);
        if (objectValue != null) {
          if (objectValue is List && objectValue.length == 2 && objectValue[0] is ObjectIdentifier && objectValue[1] is String) {
            subjectFields.add("${(objectValue[0] as ObjectIdentifier).nodes.join(".")}: ${objectValue[1] as String}");
          } else {
            subjectFields.add("$objectValue");
          }
        }
      }
    }

    Certificate certificate = Certificate(
      uuid: const Uuid().v4(),
      certificate: data["certificate"] as String,
      alias: data["alias"] as String,
      subjectDN: subjectFields.join("\n"),
      notAfterDate: notAfterDate,
      serialNumber: serialNumber,
      algorithm: algorithm,
      parameterMap: getParameterMap(cert, serialNumber, algorithm),
      certificateDescription: getCertificateDescription(cert, serialNumber, algorithm),
    );

    return certificate;
  }

  static String parseSerialNumberToHex(BigInt serialNumber) {
    String radixSerialNumber = serialNumber.toRadixString(16);
    Uint8List byteSerialNumber = ASN1Integer.encodeBigInt(serialNumber);
    return radixSerialNumber.length < byteSerialNumber.length * 2 ? radixSerialNumber.padLeft(byteSerialNumber.length * 2, "0") : radixSerialNumber;
  }

  @override
  bool operator ==(dynamic other) => (other is Certificate) && other.certificate == certificate && other.serialNumber == serialNumber;

  @override
  int get hashCode => Object.hash(certificate, serialNumber);

  static Map<String, String> getParameterMap(X509Certificate x509certificate, String serialNumber, Algorithm algorithm) => {
        "validFromDate": x509certificate.tbsCertificate.validity.notBefore.toString(),
        "validToDate": x509certificate.tbsCertificate.validity.notAfter.toString(),
        "issuer": x509certificate.tbsCertificate.issuer.toString(),
        "subject": x509certificate.tbsCertificate.subject.toString(),
        "subjectInfo": x509certificate.tbsCertificate.subject.toString(),
        "issuerInfo": x509certificate.tbsCertificate.issuer.toString(),
        "serialNumber": serialNumber,
        "signAlgoritm[name]": algorithm.name,
        "signAlgoritm[oid]": algorithm.signatureOID,
        "hashAlgoritm[alias]": algorithm.hashOID,
      };

  static String getCertificateDescription(X509Certificate x509certificate, String serialNumber, Algorithm algorithm) {
    const String DESCRIPTION_SEPARATOR = "\n";
    StringBuffer stringBuffer = StringBuffer();

    stringBuffer.write("Владелец: ${x509certificate.tbsCertificate.subject}$DESCRIPTION_SEPARATOR");
    stringBuffer.write("Серийный номер: $serialNumber$DESCRIPTION_SEPARATOR");
    stringBuffer.write("Издатель: ${x509certificate.tbsCertificate.issuer}$DESCRIPTION_SEPARATOR");
    stringBuffer.write("Алгоритм подписи:${algorithm.name}$DESCRIPTION_SEPARATOR");
    stringBuffer.write("Действует с: ${x509certificate.tbsCertificate.validity.notBefore}$DESCRIPTION_SEPARATOR");
    stringBuffer.write("Действует по: ${x509certificate.tbsCertificate.validity.notAfter}");

    return stringBuffer.toString();
  }
}
