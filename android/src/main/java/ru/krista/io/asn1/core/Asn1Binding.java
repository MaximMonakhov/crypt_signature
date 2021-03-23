package ru.krista.io.asn1.core;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

@Target(value = {ElementType.FIELD})
@Retention(RetentionPolicy.RUNTIME)
public @interface Asn1Binding {
    int order() default 0;

    boolean optional() default false;

    boolean explicit() default false;

}
