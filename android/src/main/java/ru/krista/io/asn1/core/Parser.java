package ru.krista.io.asn1.core;

import ru.krista.io.LimitedStream;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * Created by shubin on 01.10.18.
 */
public class Parser {
    private LimitedStream stream;

    public Parser(byte[] data) {
        this(new ByteArrayInputStream(data));
    }

    public Parser(InputStream inputStream) {
        super();
        stream = new LimitedStream(inputStream);
    }

    public static byte[] getDerLength(int len) {
        byte[] sz = new byte[10];
        int pos = 0;
        if (len > 127) {
            int size = 1;
            int val = len;
            while ((val >>>= 8) != 0)
                size++;

            sz[pos++] = (byte) (size | 0x80);
            for (int i = (size - 1) * 8; i >= 0; i -= 8) {
                sz[pos++] = (byte) (len >> i);
            }
        } else {
            sz[pos++] = (byte) len;
        }
        return Arrays.copyOfRange(sz, 0, pos);
    }

    public LimitedStream getStream() {
        return stream;
    }

    public void push(int limit) {
        stream.pushLimit(limit);
    }

    public void pop() {
        stream.pop();
    }

    public byte[] read(int size) throws IOException {
        byte[] data = new byte[size];
        int sz = 0;
        while (sz < data.length) {
            int r = stream.read(data, sz, data.length - sz);
            if (r > 0) sz += r;
            else throw new IOException("Поток не содержит достаточно данных для чтения");
        }
        return data;
    }


    public boolean available() {
        try {
            return stream.available() > 0;
        } catch (IOException e) {
            return false;
        }
    }

    public TagHeader readHeader() throws IOException {
        int tag = stream.read();
        int sz = stream.read();
        if (sz == -1)
            return null;
        if (sz > 128) {
            int cnt = sz - 128;
            sz = 0;
            for (int i = 0; i < cnt; i++) {
                sz <<= 8;
                sz |= this.stream.read();
            }
        }
        return new TagHeader(tag, sz);
    }

    public static abstract class Container {
        int tag;
        byte[] derSize;

        public Container(int tag) {
            super();
            this.tag = tag;
        }

        public void setTag(int tag) {
            this.tag = tag;
        }

        public abstract int getContentSize();

        public int makeSize() {
            int contentSize = getContentSize();
            derSize = getDerLength(contentSize);
            return contentSize + derSize.length + 1;
        }


        public void save(OutputStream output) throws IOException {
            output.write(tag);
            output.write(derSize);
            saveContent(output);
        }

        protected abstract void saveContent(OutputStream output) throws IOException;

    }

    public static class PrimitiveContainer extends Container {
        byte[] data;

        public PrimitiveContainer(int tag, byte[] data) {
            super(tag);
            this.data = data;
        }

        public int getContentSize() {
            return data == null ? 0 : data.length;
        }

        @Override
        protected void saveContent(OutputStream output) throws IOException {
            if (data != null)
                output.write(data);
        }
    }

    public static class ConstructableContainer extends Container {
        List<Container> items = new ArrayList<>();

        public ConstructableContainer(int tag) {
            super(tag);
        }

        public int getContentSize() {
            int sz = 0;
            for (Container container : items)
                sz += container.makeSize();
            return sz;
        }

        @Override
        protected void saveContent(OutputStream output) throws IOException {
            for (Container container : items)
                container.save(output);
        }

        public void addChild(Container item) {
            items.add(item);
        }
    }


}
