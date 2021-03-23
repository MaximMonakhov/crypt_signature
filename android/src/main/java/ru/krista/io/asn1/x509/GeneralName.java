package ru.krista.io.asn1.x509;

import ru.krista.io.asn1.IA5String;
import ru.krista.io.asn1.ObjectIdentifier;
import ru.krista.io.asn1.OctetString;
import ru.krista.io.asn1.core.*;
import ru.krista.io.asn1.x500.Name;

import java.io.IOException;

public class GeneralName extends Choice {
    @Asn1Binding()
    @Asn1Tag(value = Tag.CUSTOM0, cls = Tag.TagClass.CONTEXT_SPECIFIC)
    public Primitive otherName;
    @Asn1Binding()
    @Asn1Tag(value = Tag.CUSTOM1, cls = Tag.TagClass.CONTEXT_SPECIFIC)
    public IA5String rfc822Name;
    @Asn1Binding()
    @Asn1Tag(value = Tag.CUSTOM2, cls = Tag.TagClass.CONTEXT_SPECIFIC)
    public IA5String dNSName;
    @Asn1Binding()
    @Asn1Tag(value = Tag.CUSTOM3, cls = Tag.TagClass.CONTEXT_SPECIFIC, type = Tag.TagType.CONSTRUCTED)
    public Primitive x400Address;
    @Asn1Binding(explicit = true) //RFC не содержит указаия explicit...
    @Asn1Tag(value = Tag.CUSTOM4, cls = Tag.TagClass.CONTEXT_SPECIFIC, type = Tag.TagType.CONSTRUCTED)
    public Name directoryName;
    @Asn1Binding()
    @Asn1Tag(value = Tag.CUSTOM5, cls = Tag.TagClass.CONTEXT_SPECIFIC)
    public Primitive ediPartyName;
    @Asn1Binding()
    @Asn1Tag(value = Tag.CUSTOM6, cls = Tag.TagClass.CONTEXT_SPECIFIC)
    public IA5String uniformResourceIdentifier;
    @Asn1Binding()
    @Asn1Tag(value = Tag.CUSTOM7, cls = Tag.TagClass.CONTEXT_SPECIFIC)
    public OctetString iPAddress;
    @Asn1Binding()
    @Asn1Tag(value = Tag.CUSTOM8, cls = Tag.TagClass.CONTEXT_SPECIFIC)
    public ObjectIdentifier registeredID;

    public void readContent(Parser parser, TagHeader tagHeader) throws IOException {
        super.readContent(parser, tagHeader);
    }
}