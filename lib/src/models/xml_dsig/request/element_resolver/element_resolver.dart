// ignore_for_file: directives_ordering, one_member_abstracts

import 'package:crypt_signature/crypt_signature.dart';
import 'package:crypt_signature/src/models/xml_dsig/request/element_resolver/target_node.dart';
import 'package:xml/xml.dart';
import 'package:crypt_signature/src/utils/extensions/xml_sign_exception.dart';

/// Делигирует обязанности по нахождению узла для подписи
abstract class XmlElementResolver {
  /// Возвращает объект [TargetNode]
  ///
  /// В случае его отсутствия выбрасывает исключение [XmlElementFoundException]
  TargetNode getTargetNode(XmlDocument document);

  static const XmlElementResolver DOCUMENT = XmlElementResolverDocumentImpl();
}
