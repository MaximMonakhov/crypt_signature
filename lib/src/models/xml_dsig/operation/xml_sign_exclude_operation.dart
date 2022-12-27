import 'package:crypt_signature/src/models/xml_dsig/algorithm_info/algorithm_info.dart';
import 'package:crypt_signature/src/models/xml_dsig/const/xml_tag_names.dart';
import 'package:crypt_signature/src/models/xml_dsig/operation/xml_operation.dart';
import 'package:crypt_signature/src/models/xml_dsig/operation/xml_operation_result.dart';
import 'package:xml/xml.dart';

/// Операция исключения узла подписи из xml - документа
class XmlSignExcludeOperation implements XmlTransformOperation {
  @override
  Future<XmlTransformResult> exec(String rawXml) async {
    final XmlNode targetNode = XmlDocument.parse(rawXml);
    
    targetNode.children.
      removeWhere((el) => el is XmlElement && el.name.qualified == XmlTagNames.SIGNATURE);

    return XmlTransformResult(
      algorithm: UnnamedAlgorithmInfo('http://www.w3.org/2000/09/xmldsig#enveloped-signature'), 
      value: targetNode.toString(),
    );
  }
}
