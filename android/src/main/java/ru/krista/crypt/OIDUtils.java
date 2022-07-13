package ru.krista.crypt;

import java.io.IOException;
import java.security.PublicKey;

import ru.CryptoPro.JCP.JCP;
import ru.krista.exceptions.FatalError;
import ru.krista.io.asn1.core.OID;
import ru.krista.io.asn1.x509.PublicKeyInfo;

public abstract class OIDUtils {
    static public String getSignatureAlgorithm(PublicKeyInfo publicKeyInfo) {
        String algorithm = OID.DERToOID(publicKeyInfo.algorithmIdentifier.algorithm.getContent());

        String signatureAlgorithm;

        switch (algorithm) {
            case "1.2.643.2.2.19":
                signatureAlgorithm = JCP.RAW_GOST_EL_SIGN_NAME;
                break;
            case "1.2.643.7.1.1.1.1":
                signatureAlgorithm = JCP.RAW_GOST_SIGN_2012_256_NAME;
                break;
            case "1.2.643.7.1.1.1.2":
                signatureAlgorithm = JCP.RAW_GOST_SIGN_2012_512_NAME;
                break;
            default:
                throw new FatalError();
        }

        return signatureAlgorithm;
    }

    static public String getSignatureOid(PublicKeyInfo publicKeyInfo) {
        return OID.DERToOID(publicKeyInfo.algorithmIdentifier.algorithm.getContent());
    }


    static public String getDigestOid(PublicKeyInfo publicKeyInfo) {
        String publicKeyAlgorithmOid = getSignatureOid(publicKeyInfo);

        String digestAlgorithmOid;

        switch (publicKeyAlgorithmOid) {
            case "1.2.643.2.2.19":
                digestAlgorithmOid = "1.2.643.2.2.9";
                break;
            case "1.2.643.7.1.1.1.1":
                digestAlgorithmOid = "1.2.643.7.1.1.2.2";
                break;
            case "1.2.643.7.1.1.1.2":
                digestAlgorithmOid = "1.2.643.7.1.1.2.3";
                break;
            default: throw new IllegalArgumentException("Не удалось найти digest algorithm");
        }

        return digestAlgorithmOid;
    }
}
