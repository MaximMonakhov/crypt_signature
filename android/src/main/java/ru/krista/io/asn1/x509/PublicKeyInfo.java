package ru.krista.io.asn1.x509;

import ru.krista.exceptions.FatalError;
import ru.krista.io.asn1.BitString;
import ru.krista.io.asn1.OctetString;
import ru.krista.io.asn1.core.Asn1Binding;
import ru.krista.io.asn1.core.Parser;
import ru.krista.io.asn1.core.Struct;

import java.io.IOException;

public class PublicKeyInfo extends Struct {
    @Asn1Binding(order = 1)
    public AlgorithmIdentifier algorithmIdentifier;
    @Asn1Binding(order = 2)
    public BitString subjectPublicKey;

    public void setRayKey(byte[] key) {
        OctetString keyValue = new OctetString();
        keyValue.setContent(key);
        byte[] keyOctets = keyValue.encode();
        byte[] keyBits = new byte[keyOctets.length + 1];
        keyBits[0] = 0;
        System.arraycopy(keyOctets, 0, keyBits, 1, keyOctets.length);
        subjectPublicKey = new BitString();
        subjectPublicKey.setContent(keyBits);
    }

    public byte[] rawKey() {
        Parser parser = new Parser(subjectPublicKey.getContent());
        try {
            parser.read(1);
            OctetString keyValue = new OctetString();
            keyValue.read(parser);
            return keyValue.getContent();
        } catch (IOException e) {
            throw new FatalError(e);
        }
    }
}
