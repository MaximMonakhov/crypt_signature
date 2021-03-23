package ru.krista.io.asn1.core;

/**
 * Created by shubin on 01.10.18.
 */
public class TagHeader {
    /*DEBUG*/
    private int id;
    private boolean constructed;
    private boolean contextSpecific;

    private int tag;
    private int size;

    public TagHeader(int tag, int size) {
        super();
        this.tag = tag;
        this.size = size;
    /*DEBUG*/
        this.id = tag & Tag.MASK;
        this.constructed = ((tag & Tag.TagType.CONSTRUCTED.value())!=0);
        this.contextSpecific = ((tag & Tag.TagClass.CONTEXT_SPECIFIC.value())!=0);
    }

    public int getTag() {
        return tag;
    }

    public void setTag(int tag) {
        this.tag = tag;
    }

    public int getSize() {
        return size;
    }
}
