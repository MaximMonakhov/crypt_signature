package ru.krista.io.asn1;


import ru.krista.io.asn1.core.Asn1Tag;
import ru.krista.io.asn1.core.Tag;

import java.nio.charset.Charset;

@Asn1Tag(value = Tag.PRINTABLE_STRING)
public class PrintableString  extends Asn1String {
    @Override
    public Charset getCharset() {
        return ASCII;
    }
}
