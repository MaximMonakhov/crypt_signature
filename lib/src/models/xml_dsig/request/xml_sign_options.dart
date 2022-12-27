import 'package:crypt_signature/src/models/xml_dsig/request/canonicalization_type.dart';
import 'package:crypt_signature/src/models/xml_dsig/request/element_resolver/element_resolver.dart';
import 'package:crypt_signature/src/models/xml_dsig/request/element_resolver/element_resolver_document_impl.dart';
import 'package:crypt_signature/src/models/xml_dsig/signature_type/xml_signature_type.dart';

/// Опции подписи xml:
/// * Тип канонизации - [canonicalizationType]
/// * Тип подписи - [signatureType]
/// * Делегат для выбора элемента подписи - [elementResolver]
class XmlSignOptions {
  final CanonicalizationType canonicalizationType;
  late final XmlSignatureType signatureType;
  late final XmlElementResolver elementResolver;

  /// По - умолчанию 
  /// * Тип подписи: [XmlSignatureType.ENVELOPED]
  /// * Делегат для поиска элемента: [XmlElementResolver.DOCUMENT]
  /// * Тип канонизации: [CanonicalizationType.canonicalXml]
  XmlSignOptions({
    XmlElementResolver? elementResolver,
    XmlSignatureType? signatureType,
    this.canonicalizationType = CanonicalizationType.canonicalXml,
  }) {
    this.signatureType = signatureType ?? XmlSignatureType.ENVELOPED;
    this.elementResolver = elementResolver ?? const XmlElementResolverDocumentImpl();
  }

  XmlSignOptions copyWith({
    CanonicalizationType? canonicalizationType,
    XmlSignatureType? signatureType,
  }) => XmlSignOptions(
      canonicalizationType: canonicalizationType ?? this.canonicalizationType,
      signatureType: signatureType ?? this.signatureType,
    );
}
