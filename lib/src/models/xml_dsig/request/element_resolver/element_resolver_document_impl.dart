import 'package:crypt_signature/src/models/xml_dsig/request/element_resolver/element_resolver.dart';
import 'package:crypt_signature/src/models/xml_dsig/request/element_resolver/target_node.dart';
import 'package:xml/xml.dart';

/// Возвращает весь документ целиком
class XmlElementResolverDocumentImpl implements XmlElementResolver {
  const XmlElementResolverDocumentImpl();
  
  @override
  TargetNode getTargetNode(XmlDocument document) => TargetNode("", document);
}
