package ru.krista.io.asn1.core;

import ru.krista.exceptions.FatalError;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Spliterator;
import java.util.function.Consumer;

@Asn1Tag(value = Tag.SET, type = Tag.TagType.CONSTRUCTED)
public class SetOf<T extends Item> extends Constructable implements Iterable<T> {
    private List<T> items = new ArrayList<>();
    private Class<? extends Item> itemClass;

    @Override
    protected SetOf<T> clone() {
        SetOf<T> res = (SetOf<T>) super.clone();
        res.itemClass = itemClass;
        for (T item : items)
            res.items.add((T)item.clone());
        return res;
    }

    public T createContentItem() {
        if (itemClass != null)
            try {
                return (T) itemClass.newInstance();
            } catch (IllegalAccessException | InstantiationException e) {
                throw new FatalError(e);
            }
        throw new IllegalStateException();
    }

    public void setItemClass(Class<? extends Item> itemClass) {
        this.itemClass = itemClass;
    }

    @Override
    protected void prepareBind(Binding binding) {
        ContainerItem item = binding.getAnnotation(ContainerItem.class);
        if (item != null)
            setItemClass(item.value());
    }

    @Override
    public Iterator<T> iterator() {
        return items.iterator();
    }

    @Override
    public void forEach(Consumer<? super T> action) {
        items.forEach(action);
    }

    @Override
    public Spliterator<T> spliterator() {
        return items.spliterator();
    }

    @Override
    public Parser.Container createContainer() {
        Parser.ConstructableContainer container = new Parser.ConstructableContainer(getTag());
        for (Item i : items)
            container.addChild(i.createContainer());
        return container;
    }

    @Override
    public void readContent(Parser parser, TagHeader tagHeader) throws IOException {
        while (parser.available()) {
            T item = createContentItem();
            item.read(parser);
            addItem(item);
        }
    }

    public void addItem(T item) {
        items.add(item);
    }
}
