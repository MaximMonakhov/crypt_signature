// ignore_for_file: one_member_abstracts

import 'package:crypt_signature/src/models/xml_dsig/operation/xml_canonicalization_operation.dart';
import 'package:crypt_signature/src/models/xml_dsig/operation/xml_operation.dart';
import 'package:crypt_signature/src/models/xml_dsig/operation/xml_operation_result.dart';
import 'package:xml/xml.dart';

/// Осуществляет преобразования целевого xml - документа (**Transforms**) перед этапом вычисления хэша
abstract class XmlSignTransformer {
  Future<XmlTransformsResult> exec(XmlNode target);
}

class XmlSignTransformerImpl implements XmlSignTransformer {
  late final List<XmlTransformOperation> _operations;

  XmlSignTransformerImpl({
    required XmlCanonicalizationOperation canonicalization,
    required List<XmlTransformOperation> operations, 
  }) {
    _operations = operations.toList();
    _operations.add(canonicalization);
  }

  @override
  Future<XmlTransformsResult> exec(XmlNode target) async {
    final List<XmlTransformOperation> operations = _operations.toList();
    final List<XmlTransformResult> result = [];

    String currentRawXml = target.toString();
    
    for(final XmlTransformOperation operation in operations) {
      final XmlTransformResult transform = await operation.exec(currentRawXml);
      result.add(transform);
      currentRawXml = transform.value;
    }

    return XmlTransformsResult(result);
  }
}

class XmlTransformsResult {
  XmlTransformsResult(List<XmlTransformResult> transforms) {
    _actualTransforms = transforms.toList();
    _visibleTransforms = transforms.toList();
    _canonicalization = _getCanonicalizationResult(_visibleTransforms);
    _visibleTransforms.remove(_canonicalization);
  }

  late final List<XmlTransformResult> _actualTransforms;

  late final List<XmlTransformResult> _visibleTransforms;


  late final XmlCanonicalizationResult _canonicalization;

  /// Результат преобразований, который должен быть включены в узел `<Transforms>*</Transforms>`
  List<XmlTransformResult> get transforms => _visibleTransforms.toList();

  /// Результат канонизации
  XmlCanonicalizationResult get canonicalization => _canonicalization;

  /// Значение, полученное в результате всех transform - преобразований
  String get value => _actualTransforms.last.value;

  static XmlCanonicalizationResult _getCanonicalizationResult(List<XmlTransformResult> transforms) {
    final List<XmlCanonicalizationResult> canonicalizationList = transforms.whereType<XmlCanonicalizationResult>().toList();
    if (canonicalizationList.isEmpty) throw Exception('Ошибка канонизации xml: не удалось обнаружить канонизацию');
    return canonicalizationList.first;
  }
}
