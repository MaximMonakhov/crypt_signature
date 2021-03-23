package ru.krista.io.asn1.x500;

import ru.krista.io.asn1.core.SetOf;

import java.util.Arrays;

/**
 * Created by shubin on 02.10.18.
 */
public class RelativeDistinguishedName extends SetOf<AttributeTypeAndValue> {
    @Override
    public AttributeTypeAndValue createContentItem() {
        return new AttributeTypeAndValue();
    }

    public AttributeTypeAndValue find(byte[] oid) {
        for (AttributeTypeAndValue at : this) {
            if (Arrays.equals(at.type.getContent(), oid))
                return at;
        }
        return null;
    }
}
