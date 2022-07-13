//
// Source code recreated from a .class file by IntelliJ IDEA
// (powered by FernFlower decompiler)
//

package ru.krista.crypt.jca.pkcs7;

import java.io.IOException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.cert.CertificateException;
import java.security.cert.X509Certificate;
import java.util.Map;
import java.util.Map.Entry;

import ru.CryptoPro.JCSP.JCSP;
import ru.krista.crypt.OIDUtils;
import ru.krista.exceptions.FatalError;
import ru.krista.io.asn1.Null;
import ru.krista.io.asn1.OctetString;
import ru.krista.io.asn1.core.OID;
import ru.krista.io.asn1.core.Primitive;
import ru.krista.io.asn1.core.SequenceOf;
import ru.krista.io.asn1.x500.Name;
import ru.krista.io.asn1.x509.AlgorithmIdentifier;
import ru.krista.io.asn1.x509.CertificateSerialNumber;
import ru.krista.io.asn1.x509.GeneralName;
import ru.krista.io.asn1.x509.GeneralNames;
import ru.krista.io.asn1.x509.PublicKeyInfo;
import ru.krista.io.asn1.x509.pksc7.Attribute;
import ru.krista.io.asn1.x509.pksc7.IssuerAndSerialNumber;
import ru.krista.io.asn1.x509.pksc7.SetOfAttributes;
import ru.krista.io.asn1.x509.pksc7.SignerIdentifier;
import ru.krista.io.asn1.x509.pksc7.SignerInfo;
import ru.krista.io.asn1.x509.pksc9.ESSCertIDv2;
import ru.krista.io.asn1.x509.pksc9.IssuerSerial;
import ru.krista.io.asn1.x509.pksc9.SigningCertificateV2;

public class SignerInfoBuilder {
    private SignerInfo signerInfo;
    private String digestAlgOid;
    private String noneSignAlgOid;

    public SignerInfoBuilder(SignerInfo signerInfo, String digestAlgOid, String noneSignAlgOid) {
        super();
        this.signerInfo = signerInfo;
        this.digestAlgOid = digestAlgOid;
        this.noneSignAlgOid = noneSignAlgOid;
        signerInfo.signatureAlgorithm = AlgorithmIdentifier.withOID(this.noneSignAlgOid);
        signerInfo.signatureAlgorithm.parameters = new Null();
        signerInfo.digestAlgorithm = AlgorithmIdentifier.withOID(digestAlgOid);
        signerInfo.digestAlgorithm.parameters = new Null();
    }

    public void setSid(X509Certificate certificate) {
        this.signerInfo.sid = new SignerIdentifier();
        this.signerInfo.sid.issuerAndSerialNumber = new IssuerAndSerialNumber();
        this.signerInfo.sid.issuerAndSerialNumber.issuer = new Primitive();

        try {
            this.signerInfo.sid.issuerAndSerialNumber.issuer.decode(certificate.getIssuerX500Principal().getEncoded());
        } catch (IOException var3) {
            throw new FatalError(var3);
        }

        this.signerInfo.sid.issuerAndSerialNumber.serialNumber = new CertificateSerialNumber();
        this.signerInfo.sid.issuerAndSerialNumber.serialNumber.setContent(certificate.getSerialNumber().toByteArray());
    }

    public void addSignedAttribute(Map.Entry<String, Primitive> entry) {
        addSignedAttribute(entry.getKey(), entry.getValue());
    }

    public void addSignedAttribute(String oid, Primitive value) {
        if (signerInfo.signedAttrs == null)
            signerInfo.signedAttrs = new SetOfAttributes();
        Attribute attribute = Attribute.withOid(oid);
        attribute.values.addItem(value);
        signerInfo.signedAttrs.addItem(attribute);
    }

    public void addSigningCertificateV2(X509Certificate[] certificates) {
        SigningCertificateV2 v2 = new SigningCertificateV2();
        v2.certIDv2s = new SequenceOf<>();
        for (X509Certificate certificate : certificates) {
            ESSCertIDv2 cert = new ESSCertIDv2();
            try {
                PublicKeyInfo publicKeyInfo = new PublicKeyInfo();
                publicKeyInfo.decode(certificate.getPublicKey().getEncoded());
                MessageDigest digest = MessageDigest.getInstance(
                        OIDUtils.getDigestOid(publicKeyInfo),
                        JCSP.PROVIDER_NAME
                );
                digest.update(certificate.getEncoded());
                cert.hash = OctetString.with(digest.digest());
                cert.hashAlgorithm = AlgorithmIdentifier.withOID(digestAlgOid);
                cert.hashAlgorithm.parameters = new Null();
                cert.issuerSerial = new IssuerSerial();
                cert.issuerSerial.issuer = new GeneralNames();
                GeneralName name = new GeneralName();
                name.directoryName = new Name();
                name.directoryName.decode(certificate.getIssuerX500Principal().getEncoded());
                cert.issuerSerial.issuer.addItem(name);
                cert.issuerSerial.serialNumber = new CertificateSerialNumber();
                cert.issuerSerial.serialNumber.setContent(certificate.getSerialNumber().toByteArray());
                v2.certIDv2s.addItem(cert);
            } catch (Exception e) {
                throw new FatalError(e);
            }
        }
        addSignedAttribute(OID.PKCS9_MIME_CMS_ATTR_SIGNING_CERTIFICATE_V2, v2.asPrimitive());
    }
}
