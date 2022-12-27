part of 'xml_signature_builder.dart';


abstract class _XmlSignatureBuilderDelegate {
  late XmlBuilder _builder;

  XmlBuilder get builder => _builder;

  XmlNode getNode() {
    _builder = XmlBuilder();
    return _buildNode();
  }

  XmlNode _buildNode();
}
