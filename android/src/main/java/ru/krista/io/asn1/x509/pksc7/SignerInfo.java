package ru.krista.io.asn1.x509.pksc7;

import ru.krista.io.asn1.core.*;
import ru.krista.io.asn1.x509.AlgorithmIdentifier;

import java.io.IOException;

public class SignerInfo extends Struct {
    public static SignerInfo instantiate() {
        SignerInfo res = new SignerInfo();
        res.version = CMSVersion.v1();
        return res;
    }

    @Asn1Binding(order = 1)
    public CMSVersion version;
    @Asn1Binding(order = 2)
    public SignerIdentifier sid;
    @Asn1Binding(order = 3)
    public AlgorithmIdentifier digestAlgorithm;
    @Asn1Binding(order = 4, optional = true)
    @Asn1Tag(value = Tag.CUSTOM0, type = Tag.TagType.CONSTRUCTED, cls = Tag.TagClass.CONTEXT_SPECIFIC)
    public SetOfAttributes signedAttrs;
    @Asn1Binding(order = 5)
    public AlgorithmIdentifier signatureAlgorithm;
    @Asn1Binding(order = 6)
    public SignatureValue signature;
    @Asn1Binding(order = 7, optional = true)
    @Asn1Tag(value = Tag.CUSTOM1, type = Tag.TagType.CONSTRUCTED, cls = Tag.TagClass.CONTEXT_SPECIFIC)
    public SetOfAttributes unsignedAttrs;

    @Override
    protected void onFieldBinded(Item item) throws IOException {
        super.onFieldBinded(item);
    }
}
