package ru.krista.io.asn1.core;

import java.io.IOException;

@Asn1Tag(value = Tag.ANY)
public class Choice extends Constructable {
    @Override
    protected boolean checkTag(int readedTag) {
        int tag = getTag();
        return (tag == Tag.ANY) || (tag == readedTag);
    }

    @Override
    public Parser.Container createContainer() {
        for (Binding binding : Binding.getBinds(this.getClass())) {
            Object res = binding.get(this);
            if (res != null) {
                Parser.Container itemContainer = Item.class.cast(res).createContainer();
                if (binding.isExplicit()) {
                    Parser.ConstructableContainer espContainer = new Parser.ConstructableContainer(binding.getHolderTag());
                    espContainer.addChild(itemContainer);
                    return espContainer;
                } else {
                    if (binding.getHolderTag() != Asn1Tag.TAG_ANY)
                        itemContainer.setTag(binding.getHolderTag());
                    return itemContainer;
                }
            }
        }
        throw new BindingException("Для %s должно быть заполнено одно поле", this.getClass().getName());
    }

    @Override
    public void readContent(Parser parser, TagHeader tagHeader) throws IOException {
        bind:
        {
            for (Binding binding : Binding.getBinds(this.getClass())) {
                if (binding.isBindable(tagHeader.getTag())) {
                    assignBind(parser, binding, tagHeader);
                    break bind;
                }
            }
            throw new IOException(String.format("Не верный формат данных для %s", this.getClass().getName()));
        }
        //Финализация чтения
    }
}
