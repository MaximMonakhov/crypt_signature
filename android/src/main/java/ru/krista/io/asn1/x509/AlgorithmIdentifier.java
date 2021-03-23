package ru.krista.io.asn1.x509;

import ru.krista.io.asn1.ObjectIdentifier;
import ru.krista.io.asn1.core.*;

@Asn1Tag(value = Tag.SEQUENCE, type = Tag.TagType.CONSTRUCTED)
public class AlgorithmIdentifier extends Struct {
    public static AlgorithmIdentifier withOID(String oid) {
        AlgorithmIdentifier res = new AlgorithmIdentifier();
        res.algorithm = ObjectIdentifier.withOid(oid);
        return res;
    }

    @Asn1Binding(order = 1)
    public ObjectIdentifier algorithm;
    @Asn1Binding(order = 2, optional = true)
    @Asn1Tag(value = Asn1Tag.TAG_ANY)
    public Primitive parameters;
}
