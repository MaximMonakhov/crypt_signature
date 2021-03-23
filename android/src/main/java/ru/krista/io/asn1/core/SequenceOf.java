package ru.krista.io.asn1.core;

@Asn1Tag(value = Tag.SEQUENCE, type = Tag.TagType.CONSTRUCTED)
public class SequenceOf<T extends Item> extends SetOf<T> {
}
