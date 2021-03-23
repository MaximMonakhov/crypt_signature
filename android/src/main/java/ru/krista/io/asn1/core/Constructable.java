package ru.krista.io.asn1.core;

import java.io.IOException;

public abstract class Constructable extends Item {
    @Override
    protected Constructable clone() {
        Constructable val = Constructable.class.cast(super.clone());
        for (Binding b : Binding.getBinds(this.getClass())) {
            Item thisProp = b.get(this);
            if (thisProp != null)
                b.set(val, thisProp.clone());
        }
        return val;
    }

    protected void onFieldBinded(Item item) throws IOException {

    }

    protected Item assignBind(Parser parser, Binding binding, TagHeader tag) throws IOException {
        Item item;
        parser.push(tag.getSize());
        try {
            if (binding.isExplicit()) {
                TagHeader expTag = parser.readHeader();
                item = binding.instantiateItem(expTag);
                item.readContent(parser, expTag);
            } else {
                item = binding.instantiateItem(tag);
                item.readContent(parser, tag);
            }
        } finally {
            parser.pop();
        }
        binding.set(this, item);
        onFieldBinded(item);
        return item;
    }


    @Override
    protected boolean checkTag(int readedTag) {
        return (readedTag & Tag.TagType.CONSTRUCTED.value()) != 0;
    }

}
