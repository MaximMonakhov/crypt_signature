package ru.krista.io;

import java.io.IOException;
import java.io.InputStream;
import java.util.Stack;

/**
 * Надстройка над потоком для ограничения размера читаемых данных
 */
public class LimitedStream extends InputStream {

    private InputStream stream;
    private Stack<Integer> limits = new Stack<>();
    private int currentLimit;

    private int cursor = 0;

    public LimitedStream(InputStream stream) {
        this.stream = stream;
    }

    public void pushLimit(int size) {
        int l = cursor + size;
        limits.push(cursor + size);
        if ((currentLimit > l) || (currentLimit == 0))
            currentLimit = l;
    }

    public void pop() {
        limits.pop();
        currentLimit = 0;
        for (Integer i : limits) {
            if ((i.intValue() < currentLimit) || (currentLimit == 0)) {
                currentLimit = i.intValue();
            }
        }
    }

    public int available() throws IOException {
        return currentLimit == 0 ? super.available() : currentLimit - cursor;
    }

    @Override
    public int read() throws IOException {
        if ((currentLimit == 0) || (currentLimit > cursor)) {
            int r = stream.read();
            if (r != -1)
                cursor++;
            return r;
        } else {
            return -1;
        }
    }
}
