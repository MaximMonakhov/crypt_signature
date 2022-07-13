package ru.krista.io.asn1.x509.pksc9;

import ru.krista.io.asn1.core.Asn1Binding;
import ru.krista.io.asn1.core.Struct;
import ru.krista.io.asn1.x509.CertificateSerialNumber;
import ru.krista.io.asn1.x509.GeneralNames;

public class IssuerSerial extends Struct {
    @Asn1Binding(order = 1)
    public GeneralNames issuer;
    @Asn1Binding(order = 2)
    public CertificateSerialNumber serialNumber;
}
