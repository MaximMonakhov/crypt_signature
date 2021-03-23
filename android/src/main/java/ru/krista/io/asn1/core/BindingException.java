package ru.krista.io.asn1.core;

import ru.krista.exceptions.FatalError;

/**
 * Created by shubin on 02.10.18.
 */
public class BindingException extends FatalError{
    public BindingException() {
    }

    public BindingException(String message, Throwable cause) {
        super(message, cause);
    }

    public BindingException(Throwable cause, String format, Object... args) {
        super(cause, format, args);
    }

    public BindingException(String message) {
        super(message);
    }

    public BindingException(String format, Object... args) {
        super(format, args);
    }

    public BindingException(Throwable cause) {
        super(cause);
    }
}
