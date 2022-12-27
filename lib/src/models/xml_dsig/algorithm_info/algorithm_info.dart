/// Информация об алгоритме (*хеширования, подписи, трансформаций и канонизации*) для `XMLDSig`
abstract class AlgorithmInfo {  
  final String name;
  final String namespace;

  AlgorithmInfo({
    required this.name, 
    required this.namespace,
  });
}

class SimpleAlgorithmInfo extends AlgorithmInfo {
  SimpleAlgorithmInfo({required super.name, required super.namespace});
}

class UnnamedAlgorithmInfo implements AlgorithmInfo {
  UnnamedAlgorithmInfo(this.namespace) {
    name = _getNameAtNamespace(namespace);
  }

  @override
  late final String name;

  @override
  final String namespace;

  static String _getNameAtNamespace(String namespace) {
    final List<String> splitedData = namespace.split('/');
    if(splitedData.isEmpty) return namespace;
    return splitedData.last;
  }
}
