import 'package:crypt_signature/src/utils/xml_extentions.dart';
import 'package:xml/xml.dart';

extension XmlBuildCopy on XmlBuilder {
  static void Function(XmlBuilder, XmlNode) _getExecutor<T>(
      void Function(XmlBuilder b, T t) executor,
  ) => (XmlBuilder b, XmlNode n) => executor(b, n as T);

  static final _typeCopyExecutorMap =
      <XmlNodeType, void Function(XmlBuilder, XmlNode)>{
    XmlNodeType.ATTRIBUTE: _getExecutor(
      (b, XmlAttribute a) => b.attribute(
        a.name.qualified,
        a.value,
        namespace: a.namespaceUri,
        attributeType: a.attributeType,
      ),
    ),
    XmlNodeType.CDATA: _getExecutor((b, XmlCDATA n) => b.cdata(n.text)),
    XmlNodeType.COMMENT: _getExecutor((b, XmlComment c) => b.comment(c.text)),
    XmlNodeType.DECLARATION:
        _getExecutor((b, XmlDeclaration d) => b._copyDeclaration(d)),
    XmlNodeType.DOCUMENT_TYPE:
        _getExecutor((b, XmlDoctype dt) => b.doctype(dt.text)),
    XmlNodeType.DOCUMENT:
        _getExecutor((b, XmlDocument d) => b._copyDocOrFragment(d)),
    XmlNodeType.DOCUMENT_FRAGMENT:
        _getExecutor((b, XmlDocumentFragment d) => b._copyDocOrFragment(d)),
    XmlNodeType.ELEMENT: _getExecutor((b, XmlElement el) => b._copyElement(el)),
    XmlNodeType.PROCESSING:
        _getExecutor((b, XmlProcessing p) => b.processing(p.target, p.text)),
    XmlNodeType.TEXT: _getExecutor((b, XmlText t) => b.text(t.text)),
  };

  static void _onTypeMissing(XmlBuilder b, XmlNode n) {
    throw Exception('Ошибка копирования узла с типом ${n.nodeType}');
  }

  /// Рекурсивно добавляет узел [node] в builder
  void copy(XmlNode node) {
    final foo = _typeCopyExecutorMap[node.nodeType] ?? _onTypeMissing;
    foo(this, node);
  }

  void _copyDeclaration(XmlDeclaration d) {
    final Map<String, String> attributes = Map.fromEntries(
      d.attributes.map((a) => MapEntry(a.name.local, a.value)),
    );
    
    declaration(
      version: d.version ?? '1.0',
      encoding: d.encoding,
      attributes: attributes,
    );
  }

  void _copyDocOrFragment(XmlNode node) {
    for (final XmlNode n in node.children) {
      copy(n);
    }
  }

  void _copyElement(XmlElement el) {
    void copyInnerElements() {
      for (final XmlNode node in el.attributes) {
        copy(node);
      }

      for (final XmlNode node in el.children) {
        copy(node);
      }
    }

    element(
      el.name.qualified,
      namespace: el.namespaceUri,
      isSelfClosing: el.isSelfClosing,
      nest: copyInnerElements,
    );
  }
}

extension XmlBuilderBuildElement on XmlBuilder {
  XmlNode buildFirstElement() {
    final XmlNode fragment = buildFragment();
    final element = fragment.firstElement;
    element.detachParent(fragment);
    return element;
  }
}
