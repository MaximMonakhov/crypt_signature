package ru.krista.io.asn1;


import ru.krista.io.asn1.core.Asn1Tag;
import ru.krista.io.asn1.core.Tag;

import java.nio.charset.Charset;

@Asn1Tag(value = Tag.NUMERIC_STRING)
public class NumericString extends Asn1String {
    @Override
    public Charset getCharset() {
        return ASCII;
    }

    @Override
    public String asString() {
        return new String(getContent());
    }
}
