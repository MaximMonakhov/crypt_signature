package ru.krista.io.asn1.x500;

import ru.krista.io.asn1.core.SequenceOf;

/**
 * Created by shubin on 02.10.18.
 */
public class RDNSequence extends SequenceOf<RelativeDistinguishedName> {
    @Override
    public RelativeDistinguishedName createContentItem() {
        return new RelativeDistinguishedName();
    }
}
