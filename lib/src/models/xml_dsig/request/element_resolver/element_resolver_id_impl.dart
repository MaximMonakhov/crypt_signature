import 'package:crypt_signature/src/exceptions/xml_sign_exception.dart';
import 'package:crypt_signature/src/models/xml_dsig/const/xml_atribute_names.dart';
import 'package:crypt_signature/src/models/xml_dsig/request/element_resolver/element_resolver.dart';
import 'package:crypt_signature/src/models/xml_dsig/request/element_resolver/target_node.dart';
import 'package:xml/xml.dart';

/// Находит элемент по атрибуту `Id`
class XmlElementResolverIdImpl implements XmlElementResolver {
  final String elementID;

  /// Находит элемент по атрибуту `Id`
  const XmlElementResolverIdImpl(this.elementID);

  @override
  TargetNode getTargetNode(XmlDocument document) {
    final List<XmlElement> targets = document
      .descendantElements
      .where((el) => el.getAttribute(XmlAtributeNames.ID) == elementID)
      .toList();

    if(targets.length != 1) throw XmlElementFoundException('Invalid requested id $elementID of this document');

    return TargetNode("#$elementID", targets.first);
  }
}
