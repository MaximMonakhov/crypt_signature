package ru.krista.io.asn1;

import ru.krista.io.asn1.core.Asn1Tag;
import ru.krista.io.asn1.core.Primitive;
import ru.krista.io.asn1.core.Tag;

@Asn1Tag(value = Tag.NULL)
public class Null extends Primitive {
    private final static byte[] DATA = new byte[]{};

    public byte[] getContent() {
        return DATA;
    }
}
