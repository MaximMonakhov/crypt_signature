import 'package:crypt_signature/src/models/certificate.dart';
import 'package:crypt_signature/src/models/sign_result.dart';
import 'package:crypt_signature/src/models/xml_dsig/algorithm_info/gost_sign_algorithm_info.dart';
import 'package:crypt_signature/src/models/xml_dsig/operation/xml_operation.dart';
import 'package:crypt_signature/src/models/xml_dsig/operation/xml_operation_result.dart';
import 'package:crypt_signature/src/native/native.dart';

abstract class XmlSignOperation extends XmlOperation<String, XmlSignResult> {

}

class XmlGostSignOperation implements XmlSignOperation {
  final Certificate certificate;
  final String password;

  XmlGostSignOperation(this.certificate, this.password);

  @override
  Future<XmlSignResult> exec(String digest) async {
    final SignResult signResult = await Native.sign(certificate, password, digest);
    
    return XmlSignResult(
      algorithm: GostSignAlgorithmInfo.atName(signResult.signatureAlgorithm), 
      value: signResult.signature,
      signResult: signResult,
    );
  }
}
