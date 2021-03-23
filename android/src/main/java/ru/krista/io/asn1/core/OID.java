package ru.krista.io.asn1.core;

import ru.krista.exceptions.FatalError;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;
import java.lang.reflect.Field;
import java.lang.reflect.Modifier;
import java.math.BigInteger;
import java.util.*;
import java.util.regex.Pattern;

/**
 * Created by shubin on 03.05.17.
 */
public final class OID {
    public final static String OBJECT_CLASS = "2.5.4.0";
    /*
    CN      CommonName
    L       LocalityName
    ST      StateOrProvinceName
    O       OrganizationName
    OU      OrganizationalUnitName
    C       CountryName
    STREET  StreetAddress
    E       Email
    */
    public final static String ALIASED_ENTRY_NAME = "2.5.4.1";
    public final static String KNOWLDGE_INFORMATION = "2.5.4.2";
    @Keyword("CN")
    public final static String COMMON_NAME = "2.5.4.3";
    @Keyword("SURNAME")
    public final static String SURNAME = "2.5.4.4";
    public final static String SERIAL_NUMBER = "2.5.4.5";
    @Keyword("C")
    public final static String COUNTRY_NAME = "2.5.4.6";
    @Keyword("L")
    public final static String LOCALITY_NAME = "2.5.4.7";
    @Keyword("ST")
    public final static String STATE_OR_PROVINCE_NAME = "2.5.4.8";
    @Keyword("STREET")
    public final static String STREET_ADDRESS = "2.5.4.9";
    @Keyword("O")
    public final static String ORGANIZATION_NAME = "2.5.4.10";
    @Keyword("OU")
    public final static String ORGANIZATIONAL_UNIT_NAME = "2.5.4.11";
    @Keyword("T")
    public final static String TITLE = "2.5.4.12";
    public final static String DESCRIPTION = "2.5.4.13";
    public final static String SEARCH_GUIDE = "2.5.4.14";
    public final static String BUSINESS_CATEGORY = "2.5.4.15";
    public final static String POSTAL_ADDRESS = "2.5.4.16";
    public final static String POSTAL_CODE = "2.5.4.17";
    public final static String POST_OFFICE_BOX = "2.5.4.18";
    public final static String PHYSICAL_DELIVERY_OFFICE_NAME = "2.5.4.19";
    public final static String TELEPHONE_NUMBER = "2.5.4.20";
    public final static String TELEX_NUMBER = "2.5.4.21";
    public final static String TELETEX_TERMINAL_IDENTIFIER = "2.5.4.22";
    public final static String FACSIMILE_TELEPHONE_NUMBER = "2.5.4.23";
    public final static String X121_ADDRESS = "2.5.4.24";
    public final static String INTERNATIONAL_ISDN_NUMBER = "2.5.4.25";
    public final static String REGISTERED_ADDRESS = "2.5.4.26";
    public final static String DESTINATION_INDICATOR = "2.5.4.27";
    public final static String PREFERRED_DELIVERY_METHOD = "2.5.4.28";
    public final static String PRESENTATION_ADDRESS = "2.5.4.29";
    public final static String SUPPORTED_APPLICATION_CONTEXT = "2.5.4.30";
    public final static String MEMBER = "2.5.4.31";
    public final static String OWNER = "2.5.4.32";
    public final static String ROLE_OCCUPANT = "2.5.4.33";
    public final static String SEE_ALSO = "2.5.4.34";
    public final static String USER_PASSWORD = "2.5.4.35";
    public final static String USER_CERTIFICATE = "2.5.4.36";
    public final static String CA_CERTIFICATE = "2.5.4.37";
    public final static String AUTHORITY_REVOCATION_LIST = "2.5.4.38";
    public final static String CERTIFICATE_REVOCATION_LIST = "2.5.4.39";
    public final static String CROSS_CERTIFICATE_PAIR = "2.5.4.40";
    public final static String NAME = "2.5.4.41";
    @Keyword("GIVENNAME")
    public final static String GIVEN_NAME = "2.5.4.42";
    public final static String INITIALS = "2.5.4.43";
    public final static String GENERATION_QUALIFIER = "2.5.4.44";
    public final static String UNIQUE_IDENTIFIER = "2.5.4.45";
    public final static String DN_QUALIFIER = "2.5.4.46";
    public final static String ENHANCED_SEARCH_GUIDE = "2.5.4.47";
    public final static String PROTOCOL_INFORMATION = "2.5.4.48";
    public final static String DISTINGUISHED_NAME = "2.5.4.49";
    public final static String UNIQUE_MEMBER = "2.5.4.50";
    public final static String HOUSE_IDENTIFIER = "2.5.4.51";
    public final static String SUPPORTED_ALGORITHMS = "2.5.4.52";
    public final static String DELTA_REVOCATION_LIST = "2.5.4.53";
    public final static String ATTRIBUTE_CERTIFICATE = "2.5.4.58";
    public final static String PSEUDONYM = "2.5.4.65";
    @Keyword("OGRN")
    public final static String OGRN = "1.2.643.100.1";
    @Keyword("SNILS")
    public final static String SNILS = "1.2.643.100.3";
    @Keyword("INN")
    public final static String INN = "1.2.643.3.131.1.1";
    @Keyword("E")
    public final static String EMAIL_ADDRESS = "1.2.840.113549.1.9.1";
    public final static String AUTHORITY_KEY_IDENTIFIER_EXTENTION = "2.5.29.35";
    public final static String SUBJECT_KEY_IDENTIFIER_EXTENTION = "2.5.29.14";
    public final static String CRL_DISTRIBUTION_POINTS = "2.5.29.31";
    @Keyword("GOSTR3411-3410-2001")
    public final static String GOSTR3411_3410_2001 = "1.2.643.2.2.3";
    @Keyword("GOSTR3411-3410-94")
    public final static String GOSTR3411_3410_94 = "1.2.643.2.2.4";
    @Keyword("GOSTR3411-94")
    public final static String GOSTR3411_94 = "1.2.643.2.2.9";
    @Keyword("GOSTR3410-2001")
    public final static String GOSTR3410_2001 = "1.2.643.2.2.19";
    @Keyword("GOSTR3410-94")
    public final static String GOSTR3410_94 = "1.2.643.2.2.20";
    @Keyword("GOSTR28147-89")
    public final static String GOSTR28147_89 = "1.2.643.2.2.21";
    @Keyword("GOSTR3410-2001DH")
    public final static String GOSTR3410_2001DH = "1.2.643.2.2.98";
    @Keyword("GOSTR3410-94DH")
    public final static String GOSTR3410_94DH = "1.2.643.2.2.99";
    public final static String CHECK_OID_PATTERN = "(0|1|2)\\.\\d+(\\.\\d+)*";
    public final static String CONTENT_TYPE = "1.2.840.113549.1.9.3";
    public final static String MESSAGE_DIGEST = "1.2.840.113549.1.9.4";
    @Deprecated
    public final static String PKSC7 = "1.2.840.113549.1.7.2";

    public final static String PKCS9_SIGNING_TIME = "1.2.840.113549.1.9.5";
    public final static String PKCS9_MIME_CMS_ATTR_SIGNING_CERTIFICATE = "1.2.840.113549.1.9.16.2.12";
    public final static String PKCS9_MIME_CMS_ATTR_SIGNING_CERTIFICATE_V2 = "1.2.840.113549.1.9.16.2.47";
    public final static String PKCS9_MIME_CMS_TSTINFO = "1.2.840.113549.1.9.16.1.4";
    public final static String PKCS7_DATA = "1.2.840.113549.1.7.1";
    public final static String PKCS7_SIGNEDDATA = "1.2.840.113549.1.7.2";
    public final static String PKCS7_ENVELOPEDDATA = "1.2.840.113549.1.7.3";

    public final static String TIMESTAMP_OF_CONTENT = "1.2.840.113549.1.9.16.2.20";
    public final static String TIMESTAMP_OF_SIGNATURE = "1.2.840.113549.1.9.16.2.14";

    private static Pattern PATTERN = Pattern.compile(CHECK_OID_PATTERN);
    private static Map<String, String> OIDtoKEYWORD;
    private static Map<String, String> KEYWORDtoOID;

    static {
        KEYWORDtoOID = new HashMap<>();
        OIDtoKEYWORD = new HashMap<>();
        try {
            for (Field f : OID.class.getFields()) {
                Keyword kw;
                if (
                        f.getType().equals(String.class)
                                && f.getName().startsWith("OID_")
                                && ((f.getModifiers() & Modifier.STATIC) != 0)
                                && ((kw = f.getAnnotation(Keyword.class)) != null)) {
                    String keyword = kw.value();
                    String oid = String.class.cast(f.get(OID.class));
                    KEYWORDtoOID.put(keyword, oid);
                    OIDtoKEYWORD.put(oid, keyword);
                }
            }
        } catch (IllegalAccessException e) {
        }
    }

    private OID() {
        super();
    }

    private static byte[] SIDToBytes(BigInteger sid) {
        BigInteger bi128 = BigInteger.valueOf(128);
        if (sid.compareTo(BigInteger.ZERO) == 0) {
            return new byte[]{0};
        }
        Stack<BigInteger> splited = new Stack<>();
        while (sid.compareTo(BigInteger.ZERO) != 0) {
            splited.push(sid.mod(bi128));
            sid = sid.shiftRight(7);
        }
        byte[] result = new byte[splited.size()];
        for (int i = 0; i < result.length; i++) {
            result[i] = splited.pop().toByteArray()[0];
            if (i != result.length - 1) {
                result[i] = (byte) (result[i] | 0x80);
            }
        }

        return result;
    }

    /**
     * Преобразование формата DER в OID строку
     *
     * @param der массив байт в формате DER
     * @return OID строка
     */
    public static String DERToOID(byte[] der) {
        return DERToOID(der, false);
    }

    /**
     * Преобразование формата DER в OID строку
     *
     * @param der     массив байт в формате DER
     * @param withTag true, если начальные данные содержат DER заголовок OBJECT_IDENTIFIER
     * @return OID строка
     */
    public static String DERToOID(byte[] der, boolean withTag) {
        if (der == null)
            return null;
        List<BigInteger> data = new ArrayList<>();
        data.add(BigInteger.ZERO);
        BigInteger current = BigInteger.valueOf(0);
        for (int i = withTag ? 2 : 0; i < der.length; i++) {
            current = current.shiftLeft(7);
            byte v = der[i];
            current = current.add(BigInteger.valueOf(v & 0x7F));
            if ((v & 0x80) == 0) {
                data.add(current);
                current = BigInteger.valueOf(0);
            }
        }
        BigInteger bi = data.get(1);
        BigInteger bi40 = BigInteger.valueOf(40);
        int fi = 0;
        for (int i = 0; i < 2; i++) {
            if (bi.compareTo(bi40) >= 0) {
                bi = bi.subtract(bi40);
                fi++;
            } else
                break;
        }
        data.set(0, BigInteger.valueOf(fi));
        data.set(1, bi);
        StringBuilder builder = new StringBuilder();
        for (int i = 0; i < data.size(); i++) {
            if (i != 0)
                builder.append(".");
            builder.append(data.get(i).toString());
        }
        return builder.toString();
    }

    /**
     * Проверяет правильность формата строки OID, корреляция первого и второго разряда игнорируется
     *
     * @param oid
     * @return true, если форма OID соответсвует шаблону (0|1|2)\.\d+(\.\d+)*
     */
    public static boolean isOID(String oid) {
        return PATTERN.matcher(oid).matches();
    }

    /**
     * Проверяет правильность формата строки OID, корреляция первого и второго разряда игнорируется
     *
     * @param oid
     * @throws IllegalArgumentException если OID не соответсвует шаблону (0|1|2)\.\d+(\.\d+)*
     */
    public static void checkOID(String oid) {
        if (!isOID(oid))
            throw new IllegalArgumentException("Неверный формат OID");
    }

    /**
     * Конаертирует OID в DER массив байт
     *
     * @param oid     OID строка
     * @param withTag true, если необходимо добавить заголовок OBJECT_IDENTIFIER
     * @return массив байт в формате DER
     */
    public static byte[] OIDToDER(String oid, boolean withTag) {
        checkOID(oid);

        BigInteger bi40 = BigInteger.valueOf(40);
        ByteArrayOutputStream bos = new ByteArrayOutputStream();
        try {
            if (withTag)
                bos.write(new byte[]{Tag.OBJECT_IDENTIFIER, 0});
            String[] sids = oid.split("\\.");
            BigInteger[] intSids = new BigInteger[sids.length];
            for (int i = 0; i < sids.length; i++) {
                intSids[i] = new BigInteger(sids[i]);
            }
            int value = intSids[0].intValue();
            if (((value == 0) || (value == 1)) && intSids[1].compareTo(bi40) >= 0)
                throw new IllegalArgumentException("Неверный формат OID. Для первого разряда равного 0 или 1 второй разряд должен  быть ограничен [0..40)");

            intSids[1] = intSids[1].add(intSids[0].multiply(bi40));

            for (int i = 1; i < intSids.length; i++) {
                bos.write(SIDToBytes(intSids[i]));
            }
        } catch (IOException e) {
            throw new FatalError(e);
        }
        byte[] res = bos.toByteArray();
        if (withTag)
            res[1] = (byte) (res.length - 2);
        return res;
    }

    /**
     * Конаертирует OID в DER массив байт без заголовка
     *
     * @param oid OID строка
     * @return массив байт в формате DER
     */
    public static byte[] OIDToDER(String oid) {
        return OIDToDER(oid, false);
    }

    public static String oidToKeyword(String oid) {
        checkOID(oid);
        return OIDtoKEYWORD.getOrDefault(oid, oid);
    }

    public static String keywordToOID(String keyword) {
        if (isOID(keyword))
            return keyword;
        return KEYWORDtoOID.get(keyword);
    }

    private static int[] splitStringToInt(String value) {
        String[] splitted = value.split("\\.");
        int[] res = new int[splitted.length];
        for (int i = 0; i < splitted.length; i++)
            res[i] = Integer.valueOf(splitted[i]);
        return res;
    }

    public static int compareOIDs(String o1, String o2) {
        int[] oid1 = splitStringToInt(o1);
        int[] oid2 = splitStringToInt(o2);
        int min = Math.min(oid1.length, oid2.length);
        for (int i = 0; i < min; i++) {
            if (oid1[i] > oid2[i])
                return 1;
            if (oid1[i] < oid2[i])
                return -1;
        }
        return Integer.compare(oid1.length, oid2.length);
    }

    @Target(ElementType.FIELD)
    @Retention(RetentionPolicy.RUNTIME)
    private @interface Keyword {
        String value();
    }

    public final static class OIDMeta {
        private final byte[] oidDer;
        private final String oid;

        public OIDMeta(byte[] der, boolean withTag) {
            super();
            this.oidDer = der;
            this.oid = DERToOID(der, withTag);
        }

        public OIDMeta(byte[] der) {
            this(der, true);
        }

        public OIDMeta(String oid) {
            this(oid, true);
        }

        public OIDMeta(String oid, boolean withTag) {
            super();
            this.oid = oid;
            this.oidDer = OIDToDER(oid, withTag);
        }

        public String getOid() {
            return this.oid;
        }

        public byte[] getDer() {
            return oidDer;
        }
    }

}
