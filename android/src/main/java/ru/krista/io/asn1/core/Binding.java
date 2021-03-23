package ru.krista.io.asn1.core;

import java.lang.annotation.Annotation;
import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.util.HashMap;
import java.util.Map;
import java.util.SortedSet;
import java.util.TreeSet;

/**
 * Created by shubin on 02.10.18.
 */
public class Binding implements Comparable<Binding> {
    private static ThreadLocal<Map<Class<?>, Binding[]>> classBinding = new ThreadLocal<>();

    static {
        classBinding.set(new HashMap<Class<?>, Binding[]>());
    }

    private Field field;
    private Asn1Binding binding;
    private Asn1Tag tag;
    private Polymorphics polymorphic;
    private int fullTag;
    private int deep;

    public Binding(Field field, Asn1Tag tag, Polymorphics polymorphic, Asn1Binding binding, int deep) {
        super();
        this.polymorphic = polymorphic;
        this.field = field;
        this.binding = binding;
        this.tag = tag;
        this.fullTag = tag.value() | tag.cls().value() | tag.type().value();
        this.deep = deep;
    }

    public static Binding[] getBinds(Class<? extends Item> forClass) {
        Map<Class<?>, Binding[]> map = classBinding.get();
        Binding[] res=map.get(forClass);
        if (res==null) {
            res = getBinding(forClass);
            map.put(forClass, res);
        }
        return res;
    }

    private static Binding[] getBinding(Class<?> cls) {
        SortedSet<Binding> bindingSet = new TreeSet<>();
        int deep = 0;
        while (Constructable.class.isAssignableFrom(cls)) {
            for (Field field : cls.getDeclaredFields()) {
                Asn1Binding binding = field.getAnnotation(Asn1Binding.class);
                if (binding != null) {
                    if (!Item.class.isAssignableFrom(field.getType()))
                        throw new BindingException("Биндинг допустим только для полей класса [%s] [%s.%s]", Item.class.getName(), field.getDeclaringClass().getName(), field.getName());

                    Polymorphics polymorphics = field.getAnnotation(Polymorphics.class);
                    Asn1Tag aTag = field.getAnnotation(Asn1Tag.class);
                    if (binding.explicit() && (aTag == null))
                        throw new BindingException(
                                "Для EXPLICIT биндинга должена быть задана явно аннотация @Asn1Tag [%s.%s]",
                                field.getDeclaringClass().getName(),
                                field.getName()
                        );

                    if (aTag == null) {
                        aTag = findAsn1Tag(field.getType());
                        if (aTag == null)
                            throw new BindingException("Для класса [%s] не задана аннотация @Asn1Tag", field.getType().getName());
                    }
                    bindingSet.add(new Binding(field, aTag, polymorphics, binding, deep));
                }
            }
            cls = cls.getSuperclass();
            deep++;
        }
        return bindingSet.toArray(new Binding[bindingSet.size()]);
    }

    public static Asn1Tag findAsn1Tag(Class<?> cls) {
        while ((cls != null) && (cls != Object.class)) {
            Asn1Tag atag = cls.getAnnotation(Asn1Tag.class);
            if (atag != null)
                return atag;
            cls = cls.getSuperclass();
        }
        return null;
    }

    public <T extends Annotation> T getAnnotation(Class<T> annotationClass) {
        return field.getAnnotation(annotationClass);
    }

    public boolean isOptional() {
        return binding.optional();
    }

    public boolean isExplicit() {
        return binding.explicit();
    }

    public String getName() {
        return String.format("%s.%s", field.getDeclaringClass().getName(), field.getName());
    }

    public void set(Constructable host, Item value) {
        try {
            field.setAccessible(true);
            field.set(host, value);
        } catch (IllegalAccessException e) {
            throw new BindingException(e);
        }
    }

    public Item get(Constructable host) {
        try {
            field.setAccessible(true);
            return Item.class.cast(field.get(host));
        } catch (IllegalAccessException e) {
            throw new BindingException(e);
        }
    }

    public int getHolderTag() {
        return fullTag;
    }

    public Item instantiateItem(TagHeader tag) {
        Class<? extends Item> itemClass = field.getType().asSubclass(Item.class);
        try {
            Item item= itemClass.newInstance();
            if ((item.getTag() & Asn1Tag.SYNTETIC_MASK) == Asn1Tag.SYNTETIC_MASK)
                item.setTag(tag.getTag());
            item.prepareBind(this);
            return item;
        } catch (Exception e) {
            throw new BindingException(e);
        }
    }

    public boolean isBindable(int fullTag) {
        return (tag.value() == Asn1Tag.TAG_ANY) || (this.fullTag == fullTag);
    }

    @Override
    public int compareTo(Binding o) {
        int dc = Integer.compare(deep, o.deep);
        int oc = Integer.compare(binding.order(), o.binding.order());
        return (dc == 0) ?
                (
                        oc == 0 ?
                                field.getName().compareTo(o.field.getName())
                                : oc
                )
                : -dc;
    }


}
