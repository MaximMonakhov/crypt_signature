import 'package:crypt_signature/src/models/xml_dsig/algorithm_info/algorithm_info.dart';

/// Информация о алгоритмах ГОСТ (*хеширование и подпись*)
abstract class GostAlgorithmInfo extends AlgorithmInfo {
  final String oid;

  GostAlgorithmInfo({required super.name, required super.namespace, required this.oid});

  static const XML_PREFIX = 'urn:ietf:params:xml:ns:cpxmlsec:algorithms';
}
