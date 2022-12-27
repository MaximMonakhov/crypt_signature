import 'package:xml/xml.dart';

/// Информация о найденном элементе
class TargetNode {
  /// В случае подписи всего документа, по стандарту `XmlDSig` атрибут `URI` == ""
  final String uri;
  final XmlNode node;

  TargetNode(this.uri, this.node);
}
