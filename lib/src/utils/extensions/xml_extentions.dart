import 'dart:math';

import 'package:xml/xml.dart';

/// Позиция узла по отношению к другому узлу
enum XmlNodePosition {
  /// Перед текущим элементом
  beforeCurrent,
  /// В начало текущего элемента
  inCurrentStart,
  /// В конец текущего элемента
  inCurrentEnd,
  /// После текущего элемента
  afterCurrent
}

extension XmlUtilExtentions on XmlNode {
  bool _insertNodeOuter(XmlNode node, int indexInset) {
    final XmlNode fixedParrent = parentElement ?? root;
    final List<XmlNode> childrenList = fixedParrent.children;

    if(this == root) return false;
    final int index = childrenList.indexOf(this);
    if(index == -1) return false;
    final int targetIndex = max(0, min(index + indexInset, childrenList.length));
    childrenList.insert(targetIndex, node);
    return true;
  } 

  /// Вставляет узел [node] в позицию [position] по отношению к текущему узлу
  bool insertNode(XmlNode node, XmlNodePosition position) {
    switch(position) {
      case XmlNodePosition.afterCurrent: return _insertNodeOuter(node, 1);
      case XmlNodePosition.beforeCurrent: return _insertNodeOuter(node, -1);
      case XmlNodePosition.inCurrentStart: children.insert(0, node); return true;
      case XmlNodePosition.inCurrentEnd: children.add(node); return true;
    }
  }

  bool hasAttribute(String name, { String? namespace }) => getAttribute(name, namespace: namespace) != null;
}

extension XmlNodeFirstElement on XmlNode {
  /// Возвращает первый элемент.
  /// Если элементы отсутствуют - бросает исключение
  XmlElement get firstElement {
    final XmlElement? firstElement = firstElementChild;
    if(firstElement == null) throw Exception('First element is not found');
    return firstElement;
  }
}
