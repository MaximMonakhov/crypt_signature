package ru.krista.io.asn1.x509.pksc7;

import ru.krista.io.asn1.core.*;

public class CertificateChoice extends Choice {
    @Asn1Binding()
    @Asn1Tag(value = Tag.SEQUENCE, type = Tag.TagType.CONSTRUCTED)
    public Primitive certificate;
    @Asn1Binding()
    @Asn1Tag(value = Tag.CUSTOM0, type = Tag.TagType.CONSTRUCTED)
    public Primitive extendedCertificate;
    @Asn1Binding()
    @Asn1Tag(value = Tag.CUSTOM1, type = Tag.TagType.CONSTRUCTED)
    public Primitive v1AttrCert;
    @Asn1Binding()
    @Asn1Tag(value = Tag.CUSTOM2, type = Tag.TagType.CONSTRUCTED)
    public Primitive v2AttrCert;
    @Asn1Binding()
    @Asn1Tag(value = Tag.CUSTOM3, type = Tag.TagType.CONSTRUCTED)
    public Primitive other;
}
