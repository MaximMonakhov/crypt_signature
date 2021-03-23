package ru.krista.io.asn1.x509;

import ru.krista.io.asn1.core.Parser;
import ru.krista.io.asn1.core.SequenceOf;
import ru.krista.io.asn1.core.TagHeader;

import java.io.IOException;

/**
 * Created by shubin on 02.10.18.
 */
public class GeneralNames extends SequenceOf<GeneralName> {
    @Override
    public GeneralName createContentItem() {
        return new GeneralName();
    }

    @Override
    public void readContent(Parser parser, TagHeader tagHeader) throws IOException {
        super.readContent(parser, tagHeader);
    }
}
