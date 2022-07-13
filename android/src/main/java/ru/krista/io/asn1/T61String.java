package ru.krista.io.asn1;

import ru.krista.io.asn1.core.Asn1Tag;
import ru.krista.io.asn1.core.Tag;

import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;

@Asn1Tag(value = Tag.T61_STRING)
public class T61String extends Asn1String {
    @Override
    public Charset getCharset() {
        return StandardCharsets.ISO_8859_1;
    }
}
