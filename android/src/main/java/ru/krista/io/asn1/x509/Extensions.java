package ru.krista.io.asn1.x509;

import ru.krista.io.asn1.core.SequenceOf;

public class Extensions extends SequenceOf<Extension>{
    public Extension createContentItem() {
        return new Extension();
    }
}
