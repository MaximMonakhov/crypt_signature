package ru.krista.io.asn1.x509;

import ru.krista.io.asn1.core.SequenceOf;

/**
 * Created by shubin on 02.10.18.
 */
public class CRLDistPointsSyntax extends SequenceOf<DistributionPoint> {
    @Override
    public DistributionPoint createContentItem() {
        return new DistributionPoint();
    }
}
