abstract class XmlSignException implements Exception {
  final String? message;
  final String? details;

  XmlSignException(this.message, this.details);

  @override
  String toString() => '$message:\n${super.toString()}';
}

class XmlCanonicalizationException extends XmlSignException {
  static const String _PREFIX = 'Ошибка канонизации xml - документа';

  XmlCanonicalizationException(String? details) : super(_PREFIX, details);
}

class XmlElementFoundException extends XmlSignException {
  static const String _PREFIX = 'Целевой узел xml - документа не найден';

  XmlElementFoundException(String? details) : super(_PREFIX, details);
}

class XmlInitializeOperationException extends XmlSignException {
  static const String _PREFIX = 'Ошибка инициализации операции подписи';

  XmlInitializeOperationException(String? details) : super(_PREFIX, details);
}
