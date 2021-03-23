package ru.krista.io.asn1.x509;

import ru.krista.io.asn1.core.*;

import java.io.IOException;

/**
 * Created by shubin on 02.10.18.
 */
public class DistributionPoint extends Struct {
    @Asn1Binding(optional = true, order = 1, explicit = true) /*В rfc2459 опечатка*/
    @Asn1Tag(value = Tag.CUSTOM0, cls = Tag.TagClass.CONTEXT_SPECIFIC, type = Tag.TagType.CONSTRUCTED)
    public DistributionPointName distributionPoint;
    @Asn1Binding(optional = true, order = 2)
    @Asn1Tag(value = Tag.CUSTOM1, cls = Tag.TagClass.CONTEXT_SPECIFIC, type = Tag.TagType.CONSTRUCTED)
    public Primitive reasons;
    @Asn1Binding(optional = true, order = 3)
    @Asn1Tag(value = Tag.CUSTOM2, cls = Tag.TagClass.CONTEXT_SPECIFIC, type = Tag.TagType.CONSTRUCTED)
    public Primitive cRLIssuer;

    @Override
    protected void onFieldBinded(Item item) throws IOException {
        super.onFieldBinded(item);
    }
}
