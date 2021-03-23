package ru.krista.io.asn1.x509;

import ru.krista.io.asn1.core.Asn1Binding;
import ru.krista.io.asn1.core.Asn1Tag;
import ru.krista.io.asn1.core.Choice;
import ru.krista.io.asn1.core.Tag;
import ru.krista.io.asn1.x500.RelativeDistinguishedName;

/**
 * Created by shubin on 02.10.18.
 */
public class DistributionPointName extends Choice {
    @Asn1Binding()
    @Asn1Tag(value = Tag.CUSTOM0, cls = Tag.TagClass.CONTEXT_SPECIFIC, type = Tag.TagType.CONSTRUCTED)
    public GeneralNames fullName;
    @Asn1Binding()
    @Asn1Tag(value = Tag.CUSTOM1, cls = Tag.TagClass.CONTEXT_SPECIFIC, type = Tag.TagType.CONSTRUCTED)
    public RelativeDistinguishedName nameRelativeToCRLIssuer;

}
