package ru.krista.io.asn1;

import ru.krista.io.asn1.core.Asn1Tag;
import ru.krista.io.asn1.core.Primitive;
import ru.krista.io.asn1.core.Tag;

import java.nio.charset.StandardCharsets;
import java.time.Instant;
import java.time.format.DateTimeFormatter;
import java.util.Date;

/**
 * Created by shubin on 06.04.20.
 */

@Asn1Tag(value = Tag.UTC_TIME)
public class UtcTime extends Primitive {

    public static UtcTime now() {
        UtcTime t = new UtcTime();
        t.set(Instant.now());
        return t;
    }

    public void set(Instant instant) {
        String str = DateTimeFormatter.ISO_INSTANT.format(instant);
        byte[] raw = str.getBytes(StandardCharsets.UTF_8);
        byte[] newData = new byte[raw.length];
        int i = 2;
        int k = 0;
        while ((i<raw.length) && (raw[i]!='.')) {
            switch(raw[i]) {
                case '-':
                case ':':
                case 'T':
                    break;
                default:
                    newData[k] = raw[i];
                    k++;
                    break;
            }
            i++;
        }
        newData[k] = 'Z';
        k++;
        byte[] content = new byte[k];
        System.arraycopy(newData, 0, content, 0, k);
        setContent(content);
    }
}
