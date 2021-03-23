package ru.krista.io.asn1.core;

import java.lang.annotation.*;

@Repeatable(value = Polymorphics.class)
@Retention(RetentionPolicy.RUNTIME)
@Target(value = {ElementType.FIELD})
public @interface Polymorphic {
    Asn1Tag tag() default @Asn1Tag(value = Asn1Tag.TAG_EXPLICIT_CONSTRUCT);

    Class<? extends Item> construct() default Primitive.class;
}
