package ru.krista.exceptions;

/**
 * Фатальная ошибка. Пробрасывается, когда выполнение дальнейшего алгоритма
 * невозможно по неизвестным причинам, или исправить ситуацию невозможно
 * 
 * @author shubin
 * 
 */
public class FatalError extends RuntimeException {

	private static final long serialVersionUID = 1L;

	public FatalError() {
		super();
	}

	public FatalError(String message, Throwable cause) {
		super(message, cause);
	}

	public FatalError(Throwable cause, String format, Object... args) {
		super(String.format(format, args));
	}

	public FatalError(String message) {
		super(message);
	}

	public FatalError(String format, Object... args) {
		super(String.format(format, args));
	}

	public FatalError(Throwable cause) {
		super(cause);
	}

}
