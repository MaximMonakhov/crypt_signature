package ru.krista.io.asn1;

import ru.krista.io.asn1.core.Primitive;

import java.nio.charset.Charset;

public abstract class Asn1String extends Primitive {
    public final static Charset ASCII = Charset.forName("ASCII");
    public final static Charset UNICODE_BIG_UNMARKED = Charset.forName("UnicodeBigUnmarked");


    public abstract Charset getCharset();

    @Override
    public String asString() {
        return new String(getContent(), getCharset());
    }
}
