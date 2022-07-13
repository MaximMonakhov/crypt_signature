package ru.krista.exceptions;

public class NoPrivateKeyFound extends Exception {
    public NoPrivateKeyFound() {
        super("Приватный ключ, связанный с сертификатом, не найден");
    }
}
