package ru.krista.io.asn1;

import ru.krista.io.asn1.core.Asn1Tag;
import ru.krista.io.asn1.core.Primitive;
import ru.krista.io.asn1.core.Tag;

@Asn1Tag(value = Tag.INTEGER)
public class Int extends Primitive {
    public static Int with(byte[] value) {
        Int res = new Int();
        res.setContent(value);
        return res;
    }
}
