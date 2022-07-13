package ru.krista.io.asn1.x509.pksc9;

import ru.krista.io.asn1.core.*;

public class SigningCertificateV2 extends Struct{
    @Asn1Binding(order = 1)
    @ContainerItem(value = ESSCertIDv2.class)
    public SequenceOf<ESSCertIDv2> certIDv2s;
    @Asn1Binding(order = 2, optional = true)
    @ContainerItem(value = Primitive.class)
    public SequenceOf<Primitive> policies;
}
