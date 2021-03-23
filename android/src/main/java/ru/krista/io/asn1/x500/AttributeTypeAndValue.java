package ru.krista.io.asn1.x500;

import ru.krista.io.asn1.*;
import ru.krista.io.asn1.core.*;

/**
 * Created by shubin on 02.10.18.
 */
public class AttributeTypeAndValue extends Struct {
    @Asn1Binding(order = 1)
    public AttributeType type;

    @Asn1Binding(order = 2)
    @Asn1Tag(value = Asn1Tag.TAG_ANY)
    public Primitive value;
}
