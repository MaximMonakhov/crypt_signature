package ru.krista.io.asn1;

import ru.krista.io.asn1.core.Asn1Tag;
import ru.krista.io.asn1.core.Primitive;
import ru.krista.io.asn1.core.Tag;

@Asn1Tag(value = Tag.BOOLEAN)
public class Bool extends Primitive {
    private byte TRUE = (byte) 255;
    private byte FALSE = (byte) 0;

    public void set(boolean value) {
        setContent(new byte[]{value ? TRUE : FALSE});
    }
}
