// ignore_for_file: one_member_abstracts

import 'package:crypt_signature/src/models/xml_dsig/operation/xml_operation_result.dart';

/// Операция над данными в виде строки, например, **канонизация, исключение узла подписи, взятие хеша, подпись**
/// 
/// Возвращает [R] - потомок [XmlOperationResult] от [T]
abstract class XmlOperation<T, R extends XmlOperationResult<T>> {
  Future<R> exec(String rawData);
}

/// Подготовительная операция над документом
abstract class XmlTransformOperation extends XmlOperation<String, XmlTransformResult> { 
  
}
