package ru.krista.crypt;

import android.content.Context;
import android.util.Base64;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.security.InvalidKeyException;
import java.security.KeyStore;
import java.security.KeyStoreException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.NoSuchProviderException;
import java.security.PrivateKey;
import java.security.PublicKey;
import java.security.Security;
import java.security.Signature;
import java.security.SignatureException;
import java.security.UnrecoverableKeyException;
import java.security.cert.CertificateException;
import java.security.cert.X509Certificate;
import java.util.Collections;
import java.util.Enumeration;

import ru.CryptoPro.JCSP.CSPConfig;
import ru.CryptoPro.JCSP.CSPProviderInterface;
import ru.CryptoPro.JCSP.JCSP;
import ru.cprocsp.ACSP.tools.common.CSPLicenseConstants;
import ru.cprocsp.ACSP.tools.license.LicenseInterface;
import ru.krista.crypt.jca.pkcs7.PKCS7;
import ru.krista.crypt.jca.pkcs7.SignerInfoBuilder;
import ru.krista.exceptions.NoPrivateKeyFound;
import ru.krista.io.asn1.Null;
import ru.krista.io.asn1.ObjectIdentifier;
import ru.krista.io.asn1.OctetString;
import ru.krista.io.asn1.core.OID;
import ru.krista.io.asn1.core.SetOf;
import ru.krista.io.asn1.x509.AlgorithmIdentifier;
import ru.krista.io.asn1.x509.PublicKeyInfo;
import ru.krista.io.asn1.x509.pksc7.EncapsulatedContentInfo;
import ru.krista.io.asn1.x509.pksc7.SignatureValue;
import ru.krista.io.asn1.x509.pksc7.SignerInfo;

public class CryptSignature {
    private static CryptSignature instance = null;

    private CryptSignature() {
    }

    public static CryptSignature getInstance() {
        if (instance == null)
            instance = new CryptSignature();

        return instance;
    }

    public boolean initCSP(Context context) {
        int cspInitCode = CSPConfig.init(context);

        if (cspInitCode == CSPConfig.CSP_INIT_OK) {
            if (Security.getProvider("JCSP") == null)
                Security.addProvider(new JCSP());

            return true;
        }

        return false;
    }

    public JSONObject setLicense(String license) throws JSONException {
        CSPProviderInterface providerInfo = CSPConfig.INSTANCE.getCSPProviderInfo();
        LicenseInterface licenseInterface = providerInfo.getLicense();
        int licenseStatusCode = licenseInterface.checkAndSave(license, false);
        return checkLicenseStatus(licenseStatusCode, licenseInterface);
    }

    public JSONObject getLicense() throws JSONException {
        CSPProviderInterface providerInfo = CSPConfig.INSTANCE.getCSPProviderInfo();
        LicenseInterface licenseInterface = providerInfo.getLicense();
        return checkLicenseStatus(licenseInterface.getExistingLicenseStatus(), licenseInterface);
    }

    private JSONObject checkLicenseStatus(int licenseStatusCode, LicenseInterface licenseInterface) throws JSONException {
        int expiredThroughDays = licenseInterface.getExpiredThroughDays();
        switch (licenseStatusCode) {
            case CSPLicenseConstants.LICENSE_STATUS_OK:
            if (licenseInterface.getSerialNumber() == null || licenseInterface.getSerialNumber().equals(""))
                return getLicenseResponse(false, "Лицензия не установлена", licenseInterface);
            return getLicenseResponse(true, "Лицензия активна", licenseInterface);
            case CSPLicenseConstants.LICENSE_STATUS_INVALID:
                return getLicenseResponse(false, "Лицензия недействительна", licenseInterface);
            case CSPLicenseConstants.LICENSE_STATUS_EXPIRED:
                return getLicenseResponse(false, "Срок действия лицензии истек", licenseInterface);
            default:
                return getLicenseResponse(false, "Не удалось проверить статус лицензии", licenseInterface);
        }
    }

    private JSONObject getLicenseResponse(boolean success, String message, LicenseInterface licenseInterface) throws JSONException {
        JSONObject response = new JSONObject();
        response.put("success", success);
        response.put("message", message);
        response.put("serialNumber", licenseInterface.getSerialNumber());
        response.put("expiredThroughDays", licenseInterface.getExpiredThroughDays());
        return response;
    }

    public JSONObject addCertificate(String path, String password) throws JSONException {
        try {
            KeyStore keyStore = openKeyStore(path, password);
            String alias = findPrivateKeyAlias(keyStore);
            X509Certificate certificate = (X509Certificate) keyStore.getCertificate(alias);

            JSONObject response = new JSONObject();
            response.put("success", true);
            response.put("certificate", Base64.encodeToString(certificate.getEncoded(), Base64.NO_WRAP));
            response.put("alias", alias);
            return response;
        } catch (FileNotFoundException e) {
            return getErrorResponse("PFX файл не найден", e);
        } catch (CertificateException e) {
            return getErrorResponse("Один из сертификатов в хранилище не может быть загружен", e);
        } catch (NoSuchAlgorithmException e) {
            return getErrorResponse("Алгоритм проверки целостности не найден", e);
        } catch (NoSuchProviderException e) {
            return getErrorResponse("JCSP провайдер не найден", e);
        } catch (IOException e) {
            return getErrorResponse("Не удалось обработать контейнер при добавлении в хранилище. Проверьте правильность введенного пароля", e);
        } catch (KeyStoreException e) {
            return getErrorResponse("Не удалось получить доступ к KeyStore", e);
        } catch (NoPrivateKeyFound e) {
            return getErrorResponse("Приватный ключ, связанный с сертификатом, не найден", e);
        } catch (Exception e) {
            return getErrorResponse("Не удалось добавить сертификат в хранилище", e);
        }
    }

    private JSONObject getErrorResponse(String message, Exception e) throws JSONException {
        JSONObject response = new JSONObject();
        response.put("success", false);
        response.put("message", message);
        response.put("exception", e);
        return response;
    }

    private KeyStore openKeyStore(String path, String password) throws NoSuchProviderException, KeyStoreException, IOException, CertificateException, NoSuchAlgorithmException {
        KeyStore keyStore = KeyStore.getInstance(JCSP.PFX_STORE_NAME, JCSP.PROVIDER_NAME);
        InputStream fileInputStream = new FileInputStream(path);
        keyStore.load(fileInputStream, password.toCharArray());
        return keyStore;
    }

    private String findPrivateKeyAlias(KeyStore keyStore) throws KeyStoreException, NoPrivateKeyFound {
        Enumeration<String> aliases = keyStore.aliases();

        while (aliases.hasMoreElements()) {
            String alias = aliases.nextElement();
            if (keyStore.isKeyEntry(alias))
                return alias;
        }

        throw new NoPrivateKeyFound();
    }

    public JSONObject digest(String certificateUUID, String password, String message, Context context) throws JSONException {
        try {
            KeyStore keyStore = openKeyStore(context.getFilesDir().getParent() + "/app_flutter/certificates/" + certificateUUID + ".pfx", password);
            return digest(keyStore, message);
        } catch (FileNotFoundException e) {
            return getErrorResponse("PFX файл не найден", e);
        } catch (CertificateException e) {
            return getErrorResponse("Один из сертификатов в хранилище не может быть загружен", e);
        } catch (NoSuchAlgorithmException e) {
            return getErrorResponse("Алгоритм проверки целостности не найден", e);
        } catch (NoSuchProviderException e) {
            return getErrorResponse("JCSP провайдер не найден", e);
        } catch (IOException e) {
            return getErrorResponse("Не удалось обработать контейнер при добавлении в хранилище. Проверьте правильность введенного пароля", e);
        } catch (KeyStoreException e) {
            return getErrorResponse("Не удалось получить доступ к KeyStore", e);
        } catch (NoPrivateKeyFound e) {
            return getErrorResponse("Приватный ключ, связанный с сертификатом, не найден", e);
        } catch (Exception e) {
            return getErrorResponse("Не удалось вычислить хэш документа", e);
        }
    }

    private JSONObject digest(KeyStore keyStore, String message) throws NoPrivateKeyFound, KeyStoreException, IOException, NoSuchProviderException, NoSuchAlgorithmException, JSONException {
        String alias = findPrivateKeyAlias(keyStore);
        X509Certificate certificate = (X509Certificate) keyStore.getCertificate(alias);
        byte[] data = Base64.decode(message, Base64.DEFAULT);
        PublicKeyInfo publicKeyInfo = new PublicKeyInfo();
        publicKeyInfo.decode(certificate.getPublicKey().getEncoded());
        String digestAlgorithm = OIDUtils.getDigestOid(publicKeyInfo);
        MessageDigest md = MessageDigest.getInstance(digestAlgorithm, JCSP.PROVIDER_NAME);
        md.update(data);
        byte[] digest = md.digest();

        JSONObject response = new JSONObject();
        response.put("success", true);
        response.put("message", message);
        response.put("digestAlgorithm", digestAlgorithm);
        response.put("digest", Base64.encodeToString(digest, Base64.NO_WRAP));
        return response;
    }

    public JSONObject sign(String certificateUUID, String password, String digest, Context context) throws JSONException {
        try {
            KeyStore keyStore = openKeyStore(context.getFilesDir().getParent() + "/app_flutter/certificates/" + certificateUUID + ".pfx", password);
            return sign(keyStore, digest, password);
        } catch (FileNotFoundException e) {
            return getErrorResponse("PFX файл не найден", e);
        } catch (CertificateException e) {
            return getErrorResponse("Один из сертификатов в хранилище не может быть загружен", e);
        } catch (NoSuchAlgorithmException e) {
            return getErrorResponse("Алгоритм проверки целостности не найден", e);
        } catch (NoSuchProviderException e) {
            return getErrorResponse("JCSP провайдер не найден", e);
        } catch (IOException e) {
            return getErrorResponse("Не удалось обработать контейнер при добавлении в хранилище. Проверьте правильность введенного пароля", e);
        } catch (KeyStoreException e) {
            return getErrorResponse("Не удалось получить доступ к KeyStore", e);
        } catch (NoPrivateKeyFound e) {
            return getErrorResponse("Приватный ключ, связанный с сертификатом, не найден", e);
        } catch (UnrecoverableKeyException e) {
            return getErrorResponse("Недействительный пароль", e);
        } catch (InvalidKeyException e) {
            return getErrorResponse("Приватный ключ недействителен", e);
        } catch (Exception e) {
            return getErrorResponse("Не удалось выполнить подпись", e);
        }
    }

    private JSONObject sign(KeyStore keyStore, String digest, String password) throws NoPrivateKeyFound, KeyStoreException, UnrecoverableKeyException, NoSuchAlgorithmException, IOException, NoSuchProviderException, InvalidKeyException, SignatureException, JSONException {
        String alias = findPrivateKeyAlias(keyStore);
        X509Certificate certificate = (X509Certificate) keyStore.getCertificate(alias);
        PrivateKey privateKey = (PrivateKey) keyStore.getKey(alias, password.toCharArray());
        PublicKeyInfo publicKeyInfo = new PublicKeyInfo();
        publicKeyInfo.decode(certificate.getPublicKey().getEncoded());
        String signatureAlgorithm = OIDUtils.getSignatureAlgorithm(publicKeyInfo);
        Signature signature = Signature.getInstance(signatureAlgorithm, JCSP.PROVIDER_NAME);
        signature.initSign(privateKey);
        byte[] digestRaw = Base64.decode(digest, Base64.DEFAULT);
        signature.update(digestRaw);
        byte[] sign = signature.sign();

        JSONObject response = new JSONObject();
        response.put("success", true);
        response.put("digest", digest);
        response.put("signatureAlgorithm", signatureAlgorithm);
        response.put("signature", Base64.encodeToString(sign, Base64.NO_WRAP));
        return response;
    }

    public JSONObject createPKCS7(String certificateUUID, String password, String digest, Context context) throws JSONException {
        try {
            KeyStore keyStore = openKeyStore(context.getFilesDir().getParent() + "/app_flutter/certificates/" + certificateUUID + ".pfx", password);
            String alias = findPrivateKeyAlias(keyStore);
            X509Certificate certificate = (X509Certificate) keyStore.getCertificate(alias);

            PKCS7 pkcs7 = new PKCS7();

            PublicKeyInfo publicKeyInfo = new PublicKeyInfo();
            publicKeyInfo.decode(certificate.getPublicKey().getEncoded());
            String digestOid = OIDUtils.getDigestOid(publicKeyInfo);
            String signatureOid = OIDUtils.getSignatureOid(publicKeyInfo);

            pkcs7.content.encapContentInfo = new EncapsulatedContentInfo();
            pkcs7.content.encapContentInfo.eContentType = ObjectIdentifier.withOid(OID.PKCS7_DATA);

            pkcs7.content.digestAlgorithms = new SetOf<>();
            AlgorithmIdentifier dis = AlgorithmIdentifier.withOID(digestOid);
            dis.parameters = new Null();
            pkcs7.content.digestAlgorithms.addItem(dis);

            SignerInfo signerInfo = SignerInfo.instantiate();
            SignerInfoBuilder builder = new SignerInfoBuilder(signerInfo, digestOid, signatureOid);
            byte[] rawDigest = Base64.decode(digest, Base64.DEFAULT);
            builder.addSignedAttribute(OID.MESSAGE_DIGEST, OctetString.with(rawDigest));

            builder.setSid(certificate);

            builder.addSigningCertificateV2(new X509Certificate[]{certificate});
            JSONObject response = new JSONObject();

            response.put("success", true);
            response.put("signedAttributes", Base64.encodeToString(signerInfo.signedAttrs.encode(), Base64.NO_WRAP));

            signerInfo.signature = new SignatureValue();
            signerInfo.signature.setContent(Base64.decode("reserved", Base64.DEFAULT));
            pkcs7.content.signerInfos = new SetOf<>();
            pkcs7.content.signerInfos.addItem(signerInfo);
            pkcs7.content.attachCertificatesWholly(Collections.singleton(certificate));
            response.put("pkcs7", Base64.encodeToString(pkcs7.encode(), Base64.NO_WRAP));

            return response;
        } catch (FileNotFoundException e) {
            return getErrorResponse("PFX файл не найден", e);
        } catch (CertificateException e) {
            return getErrorResponse("Один из сертификатов в хранилище не может быть загружен", e);
        } catch (NoSuchAlgorithmException e) {
            return getErrorResponse("Алгоритм проверки целостности не найден", e);
        } catch (NoSuchProviderException e) {
            return getErrorResponse("JCSP провайдер не найден", e);
        } catch (IOException e) {
            return getErrorResponse("Не удалось обработать контейнер при добавлении в хранилище. Проверьте правильность введенного пароля", e);
        } catch (KeyStoreException e) {
            return getErrorResponse("Не удалось получить доступ к KeyStore", e);
        } catch (NoPrivateKeyFound e) {
            return getErrorResponse("Приватный ключ, связанный с сертификатом, не найден", e);
        } catch (Exception e) {
            return getErrorResponse("Не удалось создать PKCS7", e);
        }
    }

    public JSONObject addSignatureToPKCS7(String rawPKCS7, String signature) throws JSONException {
        try {
            PKCS7 pkcs7 = new PKCS7();
            pkcs7.decode(Base64.decode(rawPKCS7, Base64.DEFAULT));
            SignerInfo signerInfo = pkcs7.content.signerInfos.iterator().next();

            signerInfo.signature = new SignatureValue();
            signerInfo.signature.setContent(Base64.decode(signature, Base64.DEFAULT));

            JSONObject response = new JSONObject();
            response.put("success", true);
            response.put("pkcs7", Base64.encodeToString(pkcs7.encode(), Base64.NO_WRAP));
            return response;
        } catch (IOException e) {
            return getErrorResponse("Не удалось обработать контейнер при добавлении в хранилище. Проверьте правильность введенного пароля", e);
        } catch (Exception e) {
            return getErrorResponse("Не удалось добавить атрибуты подписи к PKCS7", e);
        }
    }
}
