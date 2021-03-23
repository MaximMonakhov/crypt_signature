package ru.krista.io.asn1.core;

import ru.krista.exceptions.FatalError;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.util.Base64;

public abstract class Item implements Cloneable {

    private int tag;

    public Item() {
        super();
        Asn1Tag tag = Binding.findAsn1Tag(this.getClass());
        this.tag = (tag != null) ? tag.value() | tag.type().value() | tag.cls().value() : Tag.ANY;
    }

    protected Item(int tag) {
        super();
        this.tag = tag;
    }

    public Primitive asPrimitive() {
        Primitive result = new Primitive();
        result.setTag(getTag());
        Parser.Container container = createContainer();
        container.makeSize();
        ByteArrayOutputStream bos = new ByteArrayOutputStream();
        try {
            container.saveContent(bos);
        } catch (IOException e) {
            throw new FatalError();
        }
        result.setContent(bos.toByteArray());
        return result;
    }

    public int getTag() {
        return tag;
    }

    public void setTag(int tag) {
        this.tag = tag;
    }

    public abstract Parser.Container createContainer();

    protected void prepareBind(Binding binding) {

    }


    public void save(OutputStream outputStream) throws IOException {
        Parser.Container container = createContainer();
        container.makeSize();
        container.save(outputStream);
    }

    protected boolean checkTag(int readedTag) {
        return (tag == Tag.ANY) || (tag == readedTag);
    }

    public void read(Parser parser) throws IOException {
        TagHeader tagHeader = parser.readHeader();
        if (tagHeader == null)
            throw new IOException("Поток не содержит необходимых данных");
        if (!checkTag(tagHeader.getTag()))
            throw new IOException(String.format("Прочитанные данные не соответсвуют требуемым для %s", this.getClass().getName()));
        tag = tagHeader.getTag();
        parser.push(tagHeader.getSize());
        try {
            readContent(parser, tagHeader);
            if (parser.available())
                throw new IOException(String.format("Поток содержит непрочитанные данные для %s", this.getClass().getName()));
        } finally {
            parser.pop();
        }
    }

    public abstract void readContent(Parser parser, TagHeader tagHeader) throws IOException;


    public void decodeContent(byte[] data) throws IOException {
        Parser parser = new Parser(data);
        readContent(parser, null);
    }

    public void decodeBase64(String data) throws IOException {
        decode(Base64.getDecoder().decode(data));
    }

    public void decode(byte[] data) throws IOException {
        Parser parser = new Parser(data);
        read(parser);
    }

    public byte[] encode() {
        ByteArrayOutputStream bos = new ByteArrayOutputStream();
        try {
            save(bos);
        } catch (IOException e) {
            throw new FatalError(e);
        }
        return bos.toByteArray();
    }

    public <T extends Item> T cloneIt() {
        return (T) clone();
    }

    @Override
    protected Item clone() {
        try {
            Item item = this.getClass().newInstance();
            item.tag = tag;
            return item;
        } catch (IllegalAccessException | InstantiationException e) {
            throw new FatalError(e);
        }
    }
}
