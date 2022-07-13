package ru.krista.io.asn1.x509.pksc7;

import ru.krista.exceptions.FatalError;
import ru.krista.io.asn1.core.*;
import ru.krista.io.asn1.x509.AlgorithmIdentifier;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.security.cert.CertificateEncodingException;
import java.security.cert.CertificateException;
import java.security.cert.CertificateFactory;
import java.security.cert.X509Certificate;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.List;

public class SignedData extends Struct {
    @Asn1Binding(order = 1)
    public CMSVersion version;

    @Asn1Binding(order = 2)
    @ContainerItem(AlgorithmIdentifier.class)
    public SetOf<AlgorithmIdentifier> digestAlgorithms;
    @Asn1Binding(order = 3)
    public EncapsulatedContentInfo encapContentInfo;
    @Asn1Binding(order = 4, optional = true)
    @Asn1Tag(value = Tag.CUSTOM0, type = Tag.TagType.CONSTRUCTED, cls = Tag.TagClass.CONTEXT_SPECIFIC)
    @ContainerItem(CertificateChoice.class)
    public SetOf<CertificateChoice> certificates;
    @Asn1Binding(order = 5, optional = true)
    @Asn1Tag(value = Tag.CUSTOM1, type = Tag.TagType.CONSTRUCTED, cls = Tag.TagClass.CONTEXT_SPECIFIC)
    public Primitive crls;
    @Asn1Binding(order = 6)
    @ContainerItem(SignerInfo.class)
    public SetOf<SignerInfo> signerInfos;


    public Collection<X509Certificate> getX509Certificates() {
        if (this.certificates == null)
            return Collections.emptyList();
        List<X509Certificate> result = new ArrayList<>();
        try {
            CertificateFactory factory = CertificateFactory.getInstance("X.509");
            for (CertificateChoice certificateChoice : this.certificates) {
                if (certificateChoice.certificate != null) {
                    result.add(X509Certificate.class.cast(factory.generateCertificate(new ByteArrayInputStream(certificateChoice.certificate.encode()))));
                }
            }
        } catch (CertificateException e) {
            throw new FatalError(e);
        }
        return result.isEmpty() ? Collections.emptyList() : result;
    }

    public void attachCertificatesWholly(Iterable<X509Certificate> certs) {
        if (certificates==null)
            certificates = new SetOf<>();
        for (X509Certificate c: certs) {
            CertificateChoice certificateChoice = new CertificateChoice();
            Primitive p = new Primitive();
            try {
                p.decode(c.getEncoded());
            } catch (IOException | CertificateEncodingException e) {
                throw new FatalError(e);
            }
            certificateChoice.certificate = p;
            certificates.addItem(certificateChoice);
        }
    }


    @Override
    protected void onFieldBinded(Item item) throws IOException {
        super.onFieldBinded(item);
    }
}
