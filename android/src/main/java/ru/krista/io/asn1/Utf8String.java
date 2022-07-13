package ru.krista.io.asn1;

import ru.krista.io.asn1.core.Asn1Tag;
import ru.krista.io.asn1.core.Tag;

import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;

@Asn1Tag(value = Tag.UTF8STRING)
public class Utf8String extends Asn1String {
    @Override
    public Charset getCharset() {
        return StandardCharsets.UTF_8;
    }
}
