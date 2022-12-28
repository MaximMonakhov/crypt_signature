import 'dart:async';

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
  final XmlSignOptions options;
  final XmlOperations operations;
  final FutureOr<XmlDocument> Function(Certificate certificate) getDocument;

  late XmlDocument _document;
  late TargetNode _target;


  final XmlSignatureBuilder _signatureBuilder = const XmlSignatureBuilderImpl();

  XmlSigner(
    this.getDocument,  
    this.options,
    this.operations,
  );

  Future<void> _init(Certificate certificate) async {
    _document = (await getDocument(certificate)).copy();
    _target = options.elementResolver.getTargetNode(_document);
  }

  Future<XMLDSIGSignResult> sign(Certificate certificate, String password) async {
    await _init(certificate);
    operations.init(certificate, password);

    final XmlTransformsResult transformsResult = await operations.transformer.exec(_target.node);
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
      referenceUri: _target.uri,
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
    final XmlDocument initialDocument = _document.copy();

    final XmlNode keyInfo = _signatureBuilder.getKeyInfo(
      certificate,
      algorithmResult.certDigest,
    );

    XmlNode signatureNode = _signatureBuilder.getSignatureNode(
      signedInfo: signedInfo,
      keyInfo: keyInfo,
      signResult: algorithmResult.signature,
    );

    options.signatureType.bindSignatureNode(signatureNode, _target.node);

    return XMLDSIGSignResult(
      algorithmResult: algorithmResult,
      document: initialDocument,
      signatureNode: signatureNode,
      signedDocument: _document,
      certificate: certificate,
    );
  }
}
