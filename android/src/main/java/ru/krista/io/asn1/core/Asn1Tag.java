package ru.krista.io.asn1.core;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

@Target(value = {ElementType.TYPE, ElementType.FIELD})
@Retention(RetentionPolicy.RUNTIME)
public @interface Asn1Tag {
    /**
     * Маска, определяющая специальный набор тэгов использующихся только как маркеры в алгоритме обработки DER структур.
     * Никакие структуры не могут быть записаны или прочитаны из DER потока с этими тэгами.
     */

    int SYNTETIC_MASK = 0xFF00;
    /*
    Тэг не определен
     */
    int TAG_UNSPECIFIED = 0xFFFF;
    /*
    Объект может иметь любой тэг, явное значение которого указано в контейнере, частью которого объект является
     */
    int TAG_ANY = 0xFFFE;
    /**
     * Значение тэга опрелеляется полимофым типом.
     */
    int TAG_EXPLICIT_CONSTRUCT = 0xFFFD;

    int value() default TAG_UNSPECIFIED;

    Tag.TagClass cls() default Tag.TagClass.UNIVERSAL;

    Tag.TagType type() default Tag.TagType.PRIMITIVE;
}
