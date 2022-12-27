import 'package:crypt_signature/src/models/sign_result.dart';
import 'package:crypt_signature/src/models/xml_dsig/algorithm_info/algorithm_info.dart';

/// Результат xml - операции
class XmlOperationResult<T> {
  final AlgorithmInfo algorithm;

  final T value;

  XmlOperationResult({
    required this.algorithm,
    required this.value,
  });
}

class XmlDigestResult extends XmlOperationResult<String> {
  XmlDigestResult({required super.algorithm, required super.value});
}

class XmlSignResult extends XmlOperationResult<String> {
  XmlSignResult({required super.algorithm, required super.value, required this.signResult});

  final SignResult signResult;
}

class XmlPreparationResult extends XmlOperationResult<String> {
  XmlPreparationResult({required super.algorithm, required super.value});
}

class XmlTransformResult extends XmlPreparationResult {
  XmlTransformResult({required super.algorithm, required super.value});
}

class XmlCanonicalizationResult extends XmlTransformResult {
  XmlCanonicalizationResult({required super.algorithm, required super.value});
}
