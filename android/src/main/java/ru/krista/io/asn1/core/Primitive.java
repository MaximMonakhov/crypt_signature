package ru.krista.io.asn1.core;

import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;

@Asn1Tag(value = Asn1Tag.TAG_ANY)
public class Primitive extends Item {
    private byte[] data;

    @Override
    protected Primitive clone() {
        Primitive val = Primitive.class.cast(super.clone());
        if (data != null) {
            val.data = new byte[data.length];
            System.arraycopy(data, 0, val.data, 0, data.length);
        }
        return val;
    }

    @Override
    public Primitive asPrimitive() {
        Primitive result = new Primitive();
        result.setTag(getTag());
        result.setContent(getContent());
        return result;
    }

    public String asString() throws UnsupportedEncodingException {
        switch (getTag()) {
            case Tag.UTF8STRING:
                return new String(getContent(), StandardCharsets.UTF_8);
            case Tag.PRINTABLE_STRING:
            case Tag.IA5_STRING:
                return new String(getContent(), Charset.forName("ASCII"));
            case Tag.BMP_STRING:
                return new String(getContent(), "UnicodeBigUnmarked");
            case Tag.T61_STRING:
                return new String(getContent(), "ISO-8859-1");
            case Tag.NUMERIC_STRING:
                return new String(getContent());
            default:
                throw new UnsupportedEncodingException(String.format("Неизвестный тип строки %d", getTag()));
        }
    }

    @Override
    public Parser.Container createContainer() {
        return new Parser.PrimitiveContainer(getTag(), data);
    }

    protected void validateContent() throws IOException {

    }

    @Override
    public void readContent(Parser parser, TagHeader tagHeader) throws IOException {
        data = parser.read(tagHeader.getSize());
        validateContent();
    }

    public byte[] getContent() {
        return data;
    }

    public void setContent(byte[] data) {
        this.data = data;
    }

}
