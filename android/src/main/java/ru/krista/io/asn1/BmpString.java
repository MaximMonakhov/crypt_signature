package ru.krista.io.asn1;

import java.nio.charset.Charset;

/**
 * Created by shubin on 03.10.18.
 */
public class BmpString extends Asn1String {
    @Override
    public Charset getCharset() {
        return UNICODE_BIG_UNMARKED;
    }
}
