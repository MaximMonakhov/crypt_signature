package ru.krista.io.asn1.x509.pksc7;

import ru.krista.io.asn1.core.*;
import ru.krista.io.asn1.x509.CertificateSerialNumber;

import java.io.IOException;

public class IssuerAndSerialNumber extends Struct{
    @Asn1Binding(order = 1)
    @Asn1Tag(value = Asn1Tag.TAG_ANY)
    public Primitive issuer;
    @Asn1Binding(order = 2)
    public CertificateSerialNumber serialNumber;
    @Override
    protected void onFieldBinded(Item item) throws IOException {
        super.onFieldBinded(item);
    }
}
