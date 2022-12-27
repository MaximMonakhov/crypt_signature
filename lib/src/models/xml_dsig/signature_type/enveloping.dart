part of 'xml_signature_type.dart';

class _EnvelopingSignature extends XmlSignatureType {
  const _EnvelopingSignature();

  @override
  void bindSignatureNode(XmlNode signatureNode, XmlNode targetNode) {
    targetNode.insertNode(signatureNode, XmlNodePosition.afterCurrent);
  }

  @override
  List<XmlTransformOperation> _getTransforms(List<XmlTransformOperation> transformsCopy) => transformsCopy;
}
