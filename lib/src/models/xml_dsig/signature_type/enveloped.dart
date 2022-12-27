part of 'xml_signature_type.dart';

class _EnvelopedSignature extends XmlSignatureType {
  const _EnvelopedSignature();

  @override
  void bindSignatureNode(XmlNode signatureNode, XmlNode targetNode) {
    targetNode.insertNode(signatureNode, XmlNodePosition.inCurrentEnd);
  }

  @override
  List<XmlTransformOperation> _getTransforms(List<XmlTransformOperation> transformsCopy) => transformsCopy;
}
