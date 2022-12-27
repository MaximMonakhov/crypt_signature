part of 'xml_signature_type.dart';

class _DetachedSignature extends XmlSignatureType {
  const _DetachedSignature();

  @override
  // ignore: prefer_expression_function_bodies
  void bindSignatureNode(XmlNode signatureNode, XmlNode targetNode) {
    return;
  }

  @override
  List<XmlTransformOperation> _getTransforms(List<XmlTransformOperation> transformsCopy) {
    final XmlSignExcludeOperation operation = XmlSignExcludeOperation();
    transformsCopy.insert(0, operation);
    return transformsCopy;
  }
}
