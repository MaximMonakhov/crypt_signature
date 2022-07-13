package ru.krista.io.asn1.x509.pksc7;

import ru.krista.io.asn1.core.Asn1Binding;
import ru.krista.io.asn1.core.Asn1Tag;
import ru.krista.io.asn1.core.Choice;
import ru.krista.io.asn1.core.Tag;

import javax.security.auth.x500.X500Principal;
import java.math.BigInteger;
import java.security.cert.X509CertSelector;

public class SignerIdentifier extends Choice {
    @Asn1Binding()
    public IssuerAndSerialNumber issuerAndSerialNumber;
    @Asn1Binding()
    @Asn1Tag(value = Tag.CUSTOM0, type = Tag.TagType.CONSTRUCTED)
    public SubjectKeyIdentifier subjectKeyIdentifier;

    public X509CertSelector getCertSelector() {
        X509CertSelector selector = new X509CertSelector();
        if (issuerAndSerialNumber != null) {
            selector.setIssuer(new X500Principal(issuerAndSerialNumber.issuer.encode()));
            selector.setSerialNumber(new BigInteger(issuerAndSerialNumber.serialNumber.getContent()));
        } else if (subjectKeyIdentifier != null) {
            selector.setSubjectKeyIdentifier(subjectKeyIdentifier.encode());
        }
        return selector;
    }


}
