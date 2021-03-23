package ru.krista.io.asn1.core;

import java.io.IOException;

@Asn1Tag(value = Tag.SEQUENCE, type = Tag.TagType.CONSTRUCTED)
public class Struct extends Constructable {
    @Override
    public Parser.Container createContainer() {
        Binding[] bindings = Binding.getBinds(this.getClass());
        Parser.ConstructableContainer container = new Parser.ConstructableContainer(getTag());
        for (Binding binding : bindings) {
            Object value = binding.get(this);
            if (value != null) {
                Parser.Container itemContainer = Item.class.cast(value).createContainer();
                if (binding.isExplicit()) {
                    Parser.ConstructableContainer espContainer = new Parser.ConstructableContainer(binding.getHolderTag());
                    espContainer.addChild(itemContainer);
                    container.addChild(espContainer);
                } else {
                    if (binding.getHolderTag() != Asn1Tag.TAG_ANY)
                        itemContainer.setTag(binding.getHolderTag());
                    container.addChild(itemContainer);
                }
            } else {
                if (!binding.isOptional())
                    throw new BindingException("Не заполнено обязательное поле объекта %s", binding.getName());
            }
        }
        return container;
    }

    @Override
    public void readContent(Parser parser, TagHeader parentTag) throws IOException {
        Binding[] bindings = Binding.getBinds(this.getClass());
        int currentItem = 0;
        TagHeader tag;
        while (currentItem < bindings.length) {
            tag = parser.readHeader();
            if (tag != null) {
                //Пропуск опциональных объектов, если таг не соответсвует
                while (currentItem < bindings.length) {
                    Binding binding = bindings[currentItem];
                    if
                            (binding.isBindable(tag.getTag())
                            || !binding.isOptional())
                        break;

                    currentItem++;
                }

                if (currentItem >= bindings.length)
                    throw new IOException(String.format("Не верный формат данных для %s", this.getClass().getName()));

                Binding binding = bindings[currentItem];
                if (!binding.isBindable(tag.getTag()))
                    throw new IOException(String.format("Не верный формат данных для %s", binding.getName()));
                try {
                    assignBind(parser, binding, tag);
                } catch (IOException e) {
                    throw new IOException(String.format("Ошибка чтения для %s", binding.getName()), e);
                }
                currentItem++;

            } else {
                while ((currentItem < bindings.length) && (bindings[currentItem].isOptional())) currentItem++;
                if (currentItem != bindings.length)
                    throw new IOException(String.format("Поток не содержит достаточно данных для формирования объекта [%s]", this.getClass().getName()));
            }
        }
    }
}
