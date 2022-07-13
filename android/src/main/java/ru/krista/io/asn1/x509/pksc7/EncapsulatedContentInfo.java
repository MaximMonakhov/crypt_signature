package ru.krista.io.asn1.x509.pksc7;

import ru.krista.io.asn1.ObjectIdentifier;
import ru.krista.io.asn1.OctetString;
import ru.krista.io.asn1.core.Asn1Binding;
import ru.krista.io.asn1.core.Asn1Tag;
import ru.krista.io.asn1.core.Struct;
import ru.krista.io.asn1.core.Tag;

public class EncapsulatedContentInfo extends Struct {
    @Asn1Binding(order = 1)
    public ObjectIdentifier eContentType;
    @Asn1Binding(order = 2, optional = true, explicit = true)
    @Asn1Tag(value = Tag.CUSTOM0, type = Tag.TagType.CONSTRUCTED, cls = Tag.TagClass.CONTEXT_SPECIFIC)
    public OctetString eContent;

    public static EncapsulatedContentInfo with(String oid, OctetString eContent) {
        EncapsulatedContentInfo res = new EncapsulatedContentInfo();
        res.eContentType = ObjectIdentifier.withOid(oid);
        res.eContent = eContent;
        return res;
    }

    public static EncapsulatedContentInfo withOID(String oid) {
        EncapsulatedContentInfo res = new EncapsulatedContentInfo();
        res.eContentType = ObjectIdentifier.withOid(oid);
        return res;
    }
}
