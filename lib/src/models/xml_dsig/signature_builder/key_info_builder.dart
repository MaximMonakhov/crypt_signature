part of 'xml_signature_builder.dart';

class _KeyInfoBuilder extends _XmlSignatureBuilderDelegate {
  final Certificate certificate;
  final XmlDigestResult certDigest;

  _KeyInfoBuilder(this.certificate, this.certDigest);

  @override
  XmlNode _buildNode() {
    builder.element(XmlTagNames.KEY_INFO, nest: () {
      _buildX509Data();
    },);
    return builder.buildFirstElement();
  }

  void _buildX509Data() {
    builder.element(XmlTagNames.X509_DATA, nest: () {
      builder.element(XmlTagNames.X509_DIGEST, nest: () {
        builder.attribute(XmlAtributeNames.ALGORITHM, certDigest.algorithm.namespace);
        builder.text(certDigest.value);
      },);

      builder.element(XmlTagNames.X509_CERTIFICATE, nest: certificate.certificate);
    },);
  }
}
