package ru.krista.io.asn1.x509.pksc7;

import ru.krista.io.asn1.core.Asn1Tag;
import ru.krista.io.asn1.core.Primitive;
import ru.krista.io.asn1.core.Tag;

import java.io.IOException;

@Asn1Tag(value = Tag.INTEGER)
public class CMSVersion extends Primitive {

    private static CMSVersion vx(byte v) {
        CMSVersion version = new CMSVersion();
        version.setContent(new byte[]{v});
        return version;
    }

    public static CMSVersion v1() {
        return vx((byte) 1);
    }

    public static CMSVersion v2() {
        return vx((byte) 2);
    }

    public static CMSVersion v3() {
        return vx((byte) 3);
    }

    public static CMSVersion v4() {
        return vx((byte) 4);
    }

    public static CMSVersion v5() {
        return vx((byte) 5);
    }

    @Override
    protected void validateContent() throws IOException {
        byte[] content = getContent();
        if ((content.length != 1) || ((content[0] & 0xFF) > 5))
            throw new IOException("Ошибочное значение версии");
    }
}
