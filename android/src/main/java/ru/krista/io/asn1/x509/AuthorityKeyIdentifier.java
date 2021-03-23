package ru.krista.io.asn1.x509;

import ru.krista.io.asn1.core.Asn1Binding;
import ru.krista.io.asn1.core.Asn1Tag;
import ru.krista.io.asn1.core.Struct;
import ru.krista.io.asn1.core.Tag;

public class AuthorityKeyIdentifier extends Struct {
    @Asn1Binding(order = 1, optional = true)
    @Asn1Tag(value = Tag.CUSTOM0, cls = Tag.TagClass.CONTEXT_SPECIFIC)
    public KeyIdentifier keyIdentifier;
    @Asn1Binding(order = 2, optional = true)
    @Asn1Tag(value = Tag.CUSTOM1, cls = Tag.TagClass.CONTEXT_SPECIFIC, type = Tag.TagType.CONSTRUCTED)
    public GeneralNames authorityCertIssuer;
    @Asn1Binding(order = 3, optional = true)
    @Asn1Tag(value = Tag.CUSTOM2, cls = Tag.TagClass.CONTEXT_SPECIFIC)
    public CertificateSerialNumber authorityCertSerialNumber;
}
