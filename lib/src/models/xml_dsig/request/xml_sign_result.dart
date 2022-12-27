import 'package:crypt_signature/crypt_signature.dart';
import 'package:crypt_signature/src/models/xml_dsig/operation/xml_operation_result.dart';
import 'package:xml/xml.dart';

class XmlSignAlgorithmResult {
  final XmlCanonicalizationResult canonicalization;
  final XmlDigestResult digest;
  final XmlSignResult signature;

  final List<XmlTransformResult> transforms;

  final XmlDigestResult certDigest;

  XmlSignAlgorithmResult({
    required this.canonicalization, 
    required this.digest, 
    required this.signature, 
    required this.certDigest,
    required this.transforms,
  });
}

class XMLDSIGSignResult extends SignResult {
  final XmlSignAlgorithmResult algorithmResult;
  final XmlDocument document;
  final XmlNode signatureNode;
  final XmlDocument signedDocument;

  factory XMLDSIGSignResult({
    required XmlSignAlgorithmResult algorithmResult,
    required XmlDocument document,
    required XmlNode signatureNode,
    required XmlDocument signedDocument,
    required Certificate certificate,
  }) {
    final XmlSignResult signature = algorithmResult.signature;
    return XMLDSIGSignResult._(
      certificate, 
      algorithmResult: algorithmResult, 
      document: document, 
      signatureNode: signatureNode, 
      signedDocument: signedDocument, 
      digest: signature.value, 
      signature: algorithmResult.digest.value, 
      signatureAlgorithm: signature.signResult.signatureAlgorithm,
    );
  }
  
  XMLDSIGSignResult._(super.certificate, {
    required this.algorithmResult,
    required this.document,
    required this.signatureNode,
    required this.signedDocument,
    required super.digest,
    required super.signature,
    required super.signatureAlgorithm,
  });

  @override
  String toString() => 'document: ${document.toXmlString(pretty: true)}\n' +
    'signatureNode: ${signatureNode.toXmlString(pretty: true)}\n' +
    'signedDocument: ${signedDocument.toXmlString(pretty: true)}';
}
