package ru.krista.io.asn1;

import ru.krista.io.asn1.core.*;

import java.io.IOException;

@Asn1Tag(value = Tag.OCTET_STRING)
public class OctetString extends Primitive {
    public static OctetString with(byte[] data) {
        OctetString octetString = new OctetString();
        octetString.setContent(data);
        return octetString;
    }

    public static class With extends OctetString {
        private Item item;

        public With(Item item) {
            super();
            this.item = item;
        }

        @Override
        public Parser.Container createContainer() {
            Parser.ConstructableContainer cc = new Parser.ConstructableContainer(getTag());
            cc.addChild(item.createContainer());
            return cc;
        }

        public void readContent(Parser parser, TagHeader tagHeader) throws IOException {
            item.read(parser);
        }

        public byte[] getContent() {
            throw new UnsupportedOperationException();
        }
    }
}
