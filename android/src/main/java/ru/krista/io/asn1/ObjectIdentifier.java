package ru.krista.io.asn1;

import ru.krista.io.asn1.core.Asn1Tag;
import ru.krista.io.asn1.core.OID;
import ru.krista.io.asn1.core.Primitive;
import ru.krista.io.asn1.core.Tag;

@Asn1Tag(value = Tag.OBJECT_IDENTIFIER)
public class ObjectIdentifier extends Primitive {
    public static ObjectIdentifier withOid(byte[] oid) {
        ObjectIdentifier res = new ObjectIdentifier();
        res.setContent(oid);
        return res;
    }

    public static ObjectIdentifier withOid(String oid) {
        return withOid(OID.OIDToDER(oid));
    }

    public void setContent(String data) {
        super.setContent(OID.OIDToDER(data));
    }

}
