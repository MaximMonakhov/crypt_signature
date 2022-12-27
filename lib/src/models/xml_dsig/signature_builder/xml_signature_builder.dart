import 'package:crypt_signature/src/models/certificate.dart';
import 'package:crypt_signature/src/models/xml_dsig/algorithm_info/algorithm_info.dart';
import 'package:crypt_signature/src/models/xml_dsig/const/xml_atribute_names.dart';
import 'package:crypt_signature/src/models/xml_dsig/const/xml_tag_names.dart';
import 'package:crypt_signature/src/models/xml_dsig/operation/xml_operation_result.dart';
import 'package:crypt_signature/src/utils/xml_builder_extentions.dart';
import 'package:xml/xml.dart';

part 'xml_signature_builder_delegate.dart';
part 'sign_info_builder.dart';
part 'key_info_builder.dart';

abstract class XmlSignatureBuilder {
  XmlNode getSignatureNode({
    required XmlNode signedInfo,
    required XmlNode keyInfo,
    required XmlSignResult signResult,
  });

  XmlNode getSignedInfoNode({
    required AlgorithmInfo signatureMethod,
    required String referenceUri,
    required XmlDigestResult digestResult,
    required List<XmlTransformResult> transforms, 
    required XmlCanonicalizationResult canonicalization,
  });

  XmlNode getKeyInfo(Certificate certificate, XmlDigestResult certDigest);
}

class XmlSignatureBuilderImpl implements XmlSignatureBuilder {
  const XmlSignatureBuilderImpl();
  
  static const SIGN_NAMESPACE = 'http://www.w3.org/2000/09/xmldsig#';

  @override
  XmlNode getSignatureNode({
    required XmlNode signedInfo,
    required XmlNode keyInfo,
    required XmlSignResult signResult,
  }) {
    final XmlBuilder builder = XmlBuilder();
    builder.element(XmlTagNames.SIGNATURE, nest: () {
      builder.attribute(XmlAtributeNames.XMLNS, SIGN_NAMESPACE);
      builder.copy(signedInfo);
      builder.element(XmlTagNames.SIGNATURE_VALUE, nest: signResult.value);
      builder.copy(keyInfo);
    },);

    return builder.buildFirstElement();
  }
  
  @override
  XmlNode getSignedInfoNode({
    required AlgorithmInfo signatureMethod,
    required String referenceUri,
    required XmlDigestResult digestResult,
    required List<XmlTransformResult> transforms, 
    required XmlCanonicalizationResult canonicalization,
  }) => _SignInfoBuilder(
      signatureMethod: signatureMethod.namespace, 
      referenceUri: referenceUri, 
      digestResult: digestResult, 
      transforms: transforms, 
      canonicalization: canonicalization,
    ).getNode();

  @override
  XmlNode getKeyInfo(Certificate certificate, XmlDigestResult certDigest) => _KeyInfoBuilder(certificate, certDigest).getNode();  
}
