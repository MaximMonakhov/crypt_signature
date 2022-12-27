import 'package:crypt_signature/src/models/certificate.dart';
import 'package:crypt_signature/src/models/xml_dsig/algorithm_info/gost_sign_algorithm_info.dart';
import 'package:crypt_signature/src/models/xml_dsig/operation/xml_operation_result.dart';
import 'package:crypt_signature/src/models/xml_dsig/request/element_resolver/target_node.dart';
import 'package:crypt_signature/src/models/xml_dsig/request/xml_operations.dart';
import 'package:crypt_signature/src/models/xml_dsig/request/xml_sign_options.dart';
import 'package:crypt_signature/src/models/xml_dsig/request/xml_sign_result.dart';
import 'package:crypt_signature/src/models/xml_dsig/signature_builder/xml_signature_builder.dart';
import 'package:crypt_signature/src/models/xml_dsig/xml_sign_transformer.dart';
import 'package:xml/xml.dart';

class XmlSigner {
  final XmlDocument document;
  late final TargetNode target;
  final XmlSignOptions options;
  final XmlOperations operations;

  final XmlSignatureBuilder _signatureBuilder = const XmlSignatureBuilderImpl();

  XmlSigner(
    this.document,    
    this.options,
    this.operations,
  ) {
    this.target = options.elementResolver.getTargetNode(this.document);
  }

  Future<XMLDSIGSignResult> sign(Certificate certificate, String password) async {
    operations.init(certificate, password);

    final XmlTransformsResult transformsResult = await operations.transformer.exec(target.node);
    final XmlDigestResult digestResult = await operations.digest.exec(transformsResult.value);
    final XmlDigestResult certDigest = await operations.digest.exec(certificate.toString());

    XmlNode signedInfo = _getSignedInfoNode(certificate, digestResult, transformsResult);

    final XmlCanonicalizationResult canonicalizedSignedInfo = await operations.canonicalization.exec(signedInfo.toXmlString(pretty: true));
    final XmlDigestResult attributesDigest = await operations.digest.exec(canonicalizedSignedInfo.value);
    final XmlSignResult signature = await operations.sign.exec(attributesDigest.value);

    final XmlSignAlgorithmResult algorithmResult = XmlSignAlgorithmResult(
      canonicalization: transformsResult.canonicalization,
      digest: digestResult,
      signature: signature,
      certDigest: certDigest,
      transforms: transformsResult.transforms,
    );

    return _getSignResult(
      signedInfo: signedInfo,
      algorithmResult: algorithmResult,
      certificate: certificate,
    );
  }

  XmlNode _getSignedInfoNode(Certificate certificate, XmlDigestResult digestResult, XmlTransformsResult transformsResult) {
    final XmlNode signedInfo = _signatureBuilder.getSignedInfoNode(
      signatureMethod: GostSignAlgorithmInfo.fromAlgorithm(certificate.algorithm),
      referenceUri: target.uri,
      digestResult: digestResult,
      transforms: transformsResult.transforms,
      canonicalization: transformsResult.canonicalization,
    );
    return signedInfo;
  }

  XMLDSIGSignResult _getSignResult({
    required XmlNode signedInfo,
    required Certificate certificate,
    required XmlSignAlgorithmResult algorithmResult,
  }) {
    final XmlDocument initialDocument = document.copy();

    final XmlNode keyInfo = _signatureBuilder.getKeyInfo(
      certificate,
      algorithmResult.certDigest,
    );

    XmlNode signatureNode = _signatureBuilder.getSignatureNode(
      signedInfo: signedInfo,
      keyInfo: keyInfo,
      signResult: algorithmResult.signature,
    );

    options.signatureType.bindSignatureNode(signatureNode, target.node);

    return XMLDSIGSignResult(
      algorithmResult: algorithmResult,
      document: initialDocument,
      signatureNode: signatureNode,
      signedDocument: document,
      certificate: certificate,
    );
  }
}
