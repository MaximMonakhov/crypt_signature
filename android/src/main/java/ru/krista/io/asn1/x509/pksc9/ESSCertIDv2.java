package ru.krista.io.asn1.x509.pksc9;

import ru.krista.io.asn1.OctetString;
import ru.krista.io.asn1.core.Asn1Binding;
import ru.krista.io.asn1.core.Struct;
import ru.krista.io.asn1.x509.AlgorithmIdentifier;


public class ESSCertIDv2 extends Struct {
    @Asn1Binding(order = 1, optional = true)
    public AlgorithmIdentifier hashAlgorithm;
    @Asn1Binding(order = 2)
    public OctetString hash;
    @Asn1Binding(order = 3, optional = true)
    public IssuerSerial issuerSerial;
}
