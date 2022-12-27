import 'package:crypt_signature/src/exceptions/xml_sign_exception.dart';
import 'package:crypt_signature/src/models/xml_dsig/algorithm_info/c14n_algorithm_info.dart';
import 'package:crypt_signature/src/models/xml_dsig/operation/xml_operation.dart';
import 'package:crypt_signature/src/models/xml_dsig/operation/xml_operation_result.dart';
import 'package:crypt_signature/src/models/xml_dsig/request/canonicalization_type.dart';
import 'package:flutter_c14n/flutter_c14n.dart';

class XmlCanonicalizationOperation implements XmlTransformOperation {
  final CanonicalizationType canonicalizationType;

  XmlCanonicalizationOperation(this.canonicalizationType);

  @override
  Future<XmlCanonicalizationResult> exec(String rawXml) async {
    try {
      return await _exec(rawXml);
    } on Exception catch(e) {
      throw XmlCanonicalizationException(e.toString());
    }
  }

  Future<XmlCanonicalizationResult> _exec(String rawXml) async {
    final C14nType c14nType = canonicalizationToC14n(canonicalizationType);
    
    final String canonicalizatedXml = await FlutterC14n.canonicalize(rawXml, c14nType);
    return XmlCanonicalizationResult(
      algorithm: CanonicalizationAlgorithmInfo(c14nType), 
      value: canonicalizatedXml,
    );
  }
}
