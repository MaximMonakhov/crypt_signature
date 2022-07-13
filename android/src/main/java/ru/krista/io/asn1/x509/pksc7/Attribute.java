package ru.krista.io.asn1.x509.pksc7;

import ru.krista.io.asn1.ObjectIdentifier;
import ru.krista.io.asn1.core.*;

/**
 * Created by shubin on 02.10.18.
 */
public class Attribute extends Struct {
    @Asn1Binding(order = 1)
    public ObjectIdentifier oid;
    @Asn1Binding(order = 2)
    @ContainerItem(Primitive.class)
    public SetOf<Primitive> values;

    public static Attribute withOid(String oid) {
        Attribute res = new Attribute();
        res.oid = ObjectIdentifier.withOid(oid);
        res.values = new SetOf<>();
        return res;
    }
}
