package ru.krista.io.asn1.x509.pksc7;

import ru.krista.io.asn1.core.SetOf;
import ru.krista.io.asn1.core.Tag;

import java.util.Arrays;

public class SetOfAttributes extends SetOf<Attribute> {
    public Attribute createContentItem() {
        return new Attribute();
    }

    public Attribute find(byte[] oid) {
        for (Attribute a : this) {
            if (Arrays.equals(a.oid.getContent(), oid))
                return a;
        }
        return null;
    }

}
