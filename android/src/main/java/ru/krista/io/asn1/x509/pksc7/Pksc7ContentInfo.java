package ru.krista.io.asn1.x509.pksc7;

import ru.krista.io.asn1.ObjectIdentifier;
import ru.krista.io.asn1.core.*;

import java.io.IOException;
import java.util.Arrays;

/**
 * Created by shubin on 02.10.18.
 */
public class Pksc7ContentInfo extends Struct {
    @Asn1Binding(order = 1)
    public ObjectIdentifier oid;
    @Asn1Binding(optional = true, explicit = true, order = 2)
    @Asn1Tag(value = Tag.CUSTOM0, type = Tag.TagType.CONSTRUCTED, cls = Tag.TagClass.CONTEXT_SPECIFIC)
    public SignedData content;

    @Override
    protected void onFieldBinded(Item item) throws IOException {
        if (item == oid) {
            if (!Arrays.equals(OID.OIDToDER(OID.PKCS7_SIGNEDDATA), oid.getContent()))
                throw new IOException(String.format("Контейнер должен иметь идентификатор PKSC7 [%s]", OID.PKCS7_SIGNEDDATA));
        }
    }
}
