package ru.krista.crypt.jca.pkcs7;

import ru.krista.io.asn1.ObjectIdentifier;
import ru.krista.io.asn1.core.OID;
import ru.krista.io.asn1.x509.pksc7.CMSVersion;
import ru.krista.io.asn1.x509.pksc7.Pksc7ContentInfo;
import ru.krista.io.asn1.x509.pksc7.SignedData;

public class PKCS7 extends Pksc7ContentInfo {
    public PKCS7() {
        oid = ObjectIdentifier.withOid(OID.PKCS7_SIGNEDDATA);
        content = new SignedData();
        content.version = CMSVersion.v1();
    }
}
