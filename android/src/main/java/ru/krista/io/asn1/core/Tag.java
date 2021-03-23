package ru.krista.io.asn1.core;

public interface Tag {
    int UNSPECIFIED = 0xFFFF;
    int ANY = 0xFFFE;

    int EOC = 0;
    int BOOLEAN = 1;
    int INTEGER = 2;
    int BIT_STRING = 3;
    int OCTET_STRING = 4;
    int NULL = 5;
    int OBJECT_IDENTIFIER = 6;
    int OBJECT_DESCRIPTOR = 7;
    int EXTERNAL = 8;
    int REAL = 9;
    int ENUMERATED = 10;
    int EMBEDDED_PDV = 11;
    int UTF8STRING = 12;
    int RELATIVE_OID = 13;
    int RESERVED1 = 14;
    int RESERVED2 = 15;
    int SEQUENCE = 16;
    int SEQUENCE_OF = 16;
    int SET = 17;
    int SET_OF = 17;
    int NUMERIC_STRING = 18;
    int PRINTABLE_STRING = 19;
    int T61_STRING = 20;
    int VIDEOTEX_STRING = 21;
    int IA5_STRING = 22;
    int UTC_TIME = 23;
    int GENERALIZED_TIME = 24;
    int GRAPHIC_STRING = 25;
    int VISIBLE_STRING = 26;
    int GENERAL_STRING = 27;
    int UNIVERSALSTRING = 28;
    int CHARACTER_STRING = 29;
    int BMP_STRING = 30;
    int LONG_FORM = 31;
    int MASK = 0b00011111;

    int CUSTOM0 = 0;
    int CUSTOM1 = 1;
    int CUSTOM2 = 2;
    int CUSTOM3 = 3;
    int CUSTOM4 = 4;
    int CUSTOM5 = 5;
    int CUSTOM6 = 6;
    int CUSTOM7 = 7;
    int CUSTOM8 = 8;
    int CUSTOM9 = 9;

    enum TagType {
        PRIMITIVE(0b00000000), CONSTRUCTED(0b00100000), MASK(0b00100000);

        private int value;

        TagType(int value) {
            this.value = value;

        }

        public int value() {
            return value;
        }
    }

    enum TagClass {
        UNIVERSAL(0b00000000), APPLICATION(0b00100000), CONTEXT_SPECIFIC(0b10000000), PRIVATE(0b11000000), MASK(0b11000000);

        private int value;

        TagClass(int value) {
            this.value = value;

        }

        public int value() {
            return value;
        }
    }

}
