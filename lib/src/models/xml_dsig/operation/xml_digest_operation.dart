import 'dart:convert';

import 'package:crypt_signature/src/models/certificate.dart';
import 'package:crypt_signature/src/models/digest_result.dart';
import 'package:crypt_signature/src/models/xml_dsig/algorithm_info/gost_digest_algorithm_info.dart';
import 'package:crypt_signature/src/models/xml_dsig/operation/xml_operation.dart';
import 'package:crypt_signature/src/models/xml_dsig/operation/xml_operation_result.dart';
import 'package:crypt_signature/src/native/native.dart';

abstract class XmlDigestOperation implements XmlOperation<String, XmlDigestResult> {
  @override
  Future<XmlDigestResult> exec(String message) async => _getDigest(base64.encode(utf8.encode(message)));

  Future<XmlDigestResult> _getDigest(String encodedMessage);
}

class XmlGostDigestOperation extends XmlDigestOperation {
  final Certificate certificate;
  final String password;

  XmlGostDigestOperation(this.certificate, this.password);

  @override
  Future<XmlDigestResult> _getDigest(String encodedMessage) async {
    final DigestResult digestResult = await Native.digest(certificate, password, encodedMessage);
  
    return XmlDigestResult(
      algorithm: GostDigestAlgorithmInfo.atOID(digestResult.digestAlgorithm),
      value: digestResult.digest,
    );
  }
}
