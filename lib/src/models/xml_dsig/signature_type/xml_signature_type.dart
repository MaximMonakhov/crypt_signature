import 'package:crypt_signature/src/models/xml_dsig/operation/xml_canonicalization_operation.dart';
import 'package:crypt_signature/src/models/xml_dsig/operation/xml_operation.dart';
import 'package:crypt_signature/src/models/xml_dsig/operation/xml_sign_exclude_operation.dart';
import 'package:crypt_signature/src/models/xml_dsig/xml_sign_transformer.dart';
import 'package:crypt_signature/src/utils/extensions/xml_extentions.dart';
import 'package:xml/xml.dart';

part 'detached.dart';
part 'enveloped.dart';
part 'enveloping.dart';

/// Тип подписи
abstract class XmlSignatureType {
  const XmlSignatureType();

  /// Внешняя по отношению к `target` - узлу
  static const XmlSignatureType ENVELOPING = _EnvelopingSignature();

  /// Включенная по отношению к `target` - узлу
  static const XmlSignatureType ENVELOPED = _EnvelopedSignature();

  /// Открепленная от документа
  static const XmlSignatureType DETACHED = _DetachedSignature();

  /// Присоединяет [signatureNode] к [targetNode]
  void bindSignatureNode(XmlNode signatureNode, XmlNode targetNode);

  /// Возвращает [XmlSignTransformer], соответствующий типу подписи
  XmlSignTransformer getTransformer(
    XmlCanonicalizationOperation canonicalization,
    List<XmlTransformOperation> transforms,
  ) {
    final List<XmlTransformOperation> fixedTransforms = _getTransforms(transforms.toList());
    return XmlSignTransformerImpl(canonicalization: canonicalization, operations: fixedTransforms);
  }

  /// Возвращает список `transforms` на основании переданной копии
  List<XmlTransformOperation> _getTransforms(List<XmlTransformOperation> transformsCopy);
}
