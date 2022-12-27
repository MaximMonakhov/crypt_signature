part of 'xml_signature_builder.dart';

class _SignInfoBuilder extends _XmlSignatureBuilderDelegate {
  final String signatureMethod;
  final String referenceUri;
  final XmlDigestResult digestResult;
  final List<XmlTransformResult> transforms;
  final XmlCanonicalizationResult canonicalization;

  _SignInfoBuilder({
    required this.signatureMethod,
    required this.referenceUri,
    required this.digestResult,
    required this.transforms, 
    required this.canonicalization,
  });

  @override
  XmlNode _buildNode() {
    builder.element(
      XmlTagNames.SIGNED_INFO, 
      nest: () {
        _buildCanonicalizationMethod(canonicalization.algorithm.namespace);
        _buildSignatureMethod(signatureMethod);
        _buildReferenceNode(
          referenceUri: referenceUri, 
          transforms: transforms, 
          canonicalization: canonicalization, 
          digestResult: digestResult,
        );
      },
    );
    return builder.buildFirstElement();
  }

   void _buildReferenceNode({
    required String referenceUri,
    required List<XmlTransformResult> transforms, 
    required XmlCanonicalizationResult canonicalization,
    required XmlDigestResult digestResult,
  }) {    
    builder.element(XmlTagNames.REFERENCE, nest: () {
      builder.attribute(XmlAtributeNames.URI, referenceUri);
      _buildTranformsNode(transforms, canonicalization);
      _buildDigestMethod(digestResult.algorithm.namespace);
      builder.element(XmlTagNames.DIGEST_VALUE, nest: digestResult.value);
    },);
  }

  void _buildTranformsNode(
    List<XmlTransformResult> transforms, 
    XmlCanonicalizationResult canonicalization,
  ) {
    builder.element(XmlTagNames.TRANSFORMS, nest: () {
        for (final XmlOperationResult<dynamic> transform in transforms) {
          _buildOperationElement(XmlTagNames.TRANSFORM, transform.algorithm.namespace);  
        }
    },);
  }

  void _buildCanonicalizationMethod(String canonicalizationAlgorithm) 
    => _buildOperationElement(XmlTagNames.CANONICALIZATION_METHOD, canonicalizationAlgorithm);

  void _buildSignatureMethod(String signAlgorithm) 
    => _buildOperationElement(XmlTagNames.SIGNATURE_METHOD, signAlgorithm);

  void _buildDigestMethod(String digestAlgorithm) 
    => _buildOperationElement(XmlTagNames.DIGEST_METHOD, digestAlgorithm);

  void _buildOperationElement(String name, String algorithm) {
    builder.element(name, nest: () {
      builder.attribute(XmlAtributeNames.ALGORITHM, algorithm);
    },);
  }
}
