package ru.krista.crypt;

import android.content.Context;
import android.util.Base64;

import androidx.annotation.NonNull;

import org.apache.commons.codec.binary.Hex;
import org.json.simple.JSONObject;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.math.BigInteger;
import java.security.KeyStore;
import java.security.MessageDigest;
import java.security.PrivateKey;
import java.security.PublicKey;
import java.security.Security;
import java.security.Signature;
import java.security.cert.CertificateEncodingException;
import java.security.cert.X509Certificate;
import java.util.Arrays;
import java.util.Enumeration;
import java.util.logging.Logger;
import java.io.PrintWriter;
import java.io.StringWriter;

import io.flutter.embedding.engine.plugins.FlutterPlugin;
import io.flutter.plugin.common.MethodCall;
import io.flutter.plugin.common.MethodChannel;
import io.flutter.plugin.common.MethodChannel.MethodCallHandler;
import io.flutter.plugin.common.MethodChannel.Result;
import io.flutter.plugin.common.PluginRegistry.Registrar;

import ru.CryptoPro.JCP.JCP;
import ru.CryptoPro.JCP.tools.JCPLogger;
import ru.CryptoPro.JCSP.CSPConfig;
import ru.CryptoPro.JCSP.CSPProviderInterface;
import ru.CryptoPro.JCSP.JCSP;
import ru.CryptoPro.JCSP.support.License;
import ru.cprocsp.ACSP.tools.common.CSPLicenseConstants;
import ru.cprocsp.ACSP.tools.common.CSPTool;
import ru.cprocsp.ACSP.tools.common.Infrastructure;
import ru.cprocsp.ACSP.tools.license.ACSPLicense;
import ru.cprocsp.ACSP.tools.license.CSPLicense;
import ru.cprocsp.ACSP.tools.license.LicenseInterface;
import ru.krista.exceptions.FatalError;
import ru.krista.io.asn1.core.OID;
import ru.krista.io.asn1.x509.PublicKeyInfo;

/**
 * CryptSignaturePlugin
 */
public class CryptSignaturePlugin implements FlutterPlugin, MethodCallHandler {
    public static final int INIT_CSP_OK = 0;
    public static final int INIT_CSP_LICENSE_ERROR = 1;
    public static final int INIT_CSP_ERROR = -1;

    private Context context;
    private final Logger log = Logger.getLogger(this.getClass().getName());
    private MethodChannel channel;

    @Override
    public void onAttachedToEngine(@NonNull FlutterPluginBinding flutterPluginBinding) {
        channel = new MethodChannel(flutterPluginBinding.getBinaryMessenger(), "crypt_signature");
        channel.setMethodCallHandler(this);
        context = flutterPluginBinding.getApplicationContext();
    }

    @Override
    public void onMethodCall(@NonNull MethodCall call, @NonNull Result result) {
        switch (call.method) {
            case "initCSP": {
                int resulty;

                try {
                    String license = call.argument("license");
                    resulty = initCSP(license);
                    if (resulty == INIT_CSP_OK)
                        result.success(resulty);
                    else result.error("ERROR", "Ошибка при инициализации провайдера", resulty);
                } catch (Exception e) {
                    result.error("ERROR", "Ошибка при инициализации провайдера: " + e.getMessage(), INIT_CSP_ERROR);
                }

                break;
            }
            case "installCertificate": {
                String path = call.argument("pathToCert");
                String password = call.argument("password");

                MethodResponse<String> resulty = installCertificate(path, password);

                if (resulty.code == MethodResponseCode.SUCCESS)
                    result.success(resulty.content);
                else result.error("ERROR", resulty.content, null);
                break;
            }
            case "sign": {
                String uuid = call.argument("uuid");
                String password = call.argument("password");
                String data = call.argument("data");

                MethodResponse<String> resulty = sign(uuid, password, data);

                if (resulty.code == MethodResponseCode.SUCCESS)
                    result.success(resulty.content);
                else result.error("ERROR", new String(resulty.content), null);
                break;
            }
            default:
                result.notImplemented();
        }
    }

    @Override
    public void onDetachedFromEngine(@NonNull FlutterPluginBinding binding) {
        channel.setMethodCallHandler(null);
    }

    private int initCSP(String license) throws Exception {
        log.info("Инициализация провайдера CSP");
        log.info("Лицензия: " + license);

        int initCode = CSPConfig.init(context);
        log.info("Код инициализации провайдера: " + initCode);

        if (initCode == CSPConfig.CSP_INIT_OK) {
            log.info("Провайдер инициализирован");

            if (Security.getProvider("JCSP") == null)
                Security.addProvider(new JCSP());

            int licenseStatus = setLicense(license);

            if (licenseStatus != CSPConfig.LICENSE_STATUS_OK) return INIT_CSP_LICENSE_ERROR;

            return INIT_CSP_OK;
        }

        log.info("Провайдер не инициализирован");
        return INIT_CSP_ERROR;
    }

    private int setLicense(String license) {
        CSPProviderInterface providerInfo = CSPConfig.INSTANCE.getCSPProviderInfo();
        LicenseInterface licenseInterface = providerInfo.getLicense();
        return licenseInterface.checkAndSave(license, false);
    }

    private MethodResponse<String> installCertificate(String path, String password) {
        log.info("Установка сертификата: path - " + path);

        try {
            KeyStore keyStorePFX = KeyStore.getInstance(JCSP.PFX_STORE_NAME, JCSP.PROVIDER_NAME);
            InputStream fileInputStream = new FileInputStream(path);

            keyStorePFX.load(fileInputStream, password.toCharArray());

            String alias = null;
            Enumeration<String> aliasesPFX = keyStorePFX.aliases();

            log.info("Получение списка сертификатов");

            while (aliasesPFX.hasMoreElements()) {
                String aliasPFX = aliasesPFX.nextElement();
                log.info("Сертификат: " + aliasPFX);
                if (keyStorePFX.isKeyEntry(aliasPFX)) {
                    log.info("Сертификат связанный с приватным ключем: " + aliasPFX);
                    alias = aliasPFX;
                }
            }

            if (alias != null) {
                log.info("Сертификат распакован");
                X509Certificate certificate = (X509Certificate) keyStorePFX.getCertificate(alias);
                String certificateInfo = getCertificateInfo(certificate, alias);

                return new MethodResponse<String>(certificateInfo, MethodResponseCode.SUCCESS);
            } else {
                log.info("Сертификат не распакован");
                throw new Exception("Ошибка при импорте *.pfx сертификата");
            }
        } catch (Exception exception) {
            log.info("Ошибка при чтении сертификата");
            return new MethodResponse<String>("Ошибка: " + exception.toString(), MethodResponseCode.ERROR);
        }
    }

    private String getCertificateInfo(X509Certificate certificate, String alias) throws CertificateEncodingException, IOException {
        JSONObject obj = new JSONObject();
        obj.put("certificate", Base64.encodeToString(certificate.getEncoded(), Base64.NO_WRAP));
        obj.put("alias", alias);
        obj.put("issuerDN", certificate.getSubjectDN().toString());
        obj.put("notAfterDate", certificate.getNotAfter().toString());
        obj.put("serialNumber", new String(Hex.encodeHex(certificate.getSerialNumber().toByteArray())));
        obj.put("algorithm", certificate.getPublicKey().getAlgorithm());
        obj.put("parameterMap", getParameterMap(certificate));
        obj.put("certificateDescription", getCertificateDescription(certificate));

        return obj.toJSONString();
    }

    private String getParameterMap(X509Certificate certificate) throws IOException {
        StringBuilder stringBuilder = new StringBuilder();

        stringBuilder.append("validFromDate=").append(certificate.getNotBefore().toString()).append("&");
        stringBuilder.append("validToDate=").append(certificate.getNotAfter().toString()).append("&");
        stringBuilder.append("issuer=").append(certificate.getIssuerX500Principal().getName()).append("&");
        stringBuilder.append("subject=").append(certificate.getSubjectX500Principal().getName()).append("&");
        stringBuilder.append("subjectInfo=").append(certificate.getSubjectDN().getName()).append("&");
        stringBuilder.append("issuerInfo=").append(certificate.getIssuerDN().getName()).append("&");
        stringBuilder.append("serialNumber=").append(new String(Hex.encodeHex(certificate.getSerialNumber().toByteArray()))).append("&");
        stringBuilder.append("signAlgoritm[name]=").append(certificate.getSigAlgName()).append("&");
        stringBuilder.append("signAlgoritm[oid]=").append(certificate.getSigAlgOID()).append("&");
        stringBuilder.append("hashAlgoritm[alias]=").append(getDigestAlgorithm(certificate.getPublicKey()));

        return stringBuilder.toString();
    }

    private String getCertificateDescription(X509Certificate certificate) {
        StringBuilder stringBuilder = new StringBuilder();

        stringBuilder.append("Владелец: ").append(certificate.getSubjectX500Principal().getName()).append("\n");
        stringBuilder.append("Серийный номер: ").append(new String(Hex.encodeHex(certificate.getSerialNumber().toByteArray()))).append("\n");
        stringBuilder.append("Издатель: ").append(certificate.getIssuerX500Principal().getName()).append("\n");
        stringBuilder.append("Алгоритм подписи: ").append(certificate.getSigAlgName()).append("\n");
        stringBuilder.append("     oid: ").append(certificate.getSigAlgOID()).append("\n");
        stringBuilder.append("Действует с: ").append(certificate.getNotBefore().toString()).append("\n");
        stringBuilder.append("Действует по: ").append(certificate.getNotAfter().toString()).append("\n");

        return stringBuilder.toString();
    }

    private String getDigestAlgorithm(PublicKey publicKey) throws IOException {
        PublicKeyInfo publicKeyInfo = new PublicKeyInfo();
        publicKeyInfo.decode(publicKey.getEncoded());

        String algorithm = OID.DERToOID(publicKeyInfo.algorithmIdentifier.algorithm.getContent());

        String digestAlgorithm;

        switch (algorithm) {
            case "1.2.643.2.2.19":
                digestAlgorithm = "1.2.643.2.2.9";
                break;
            case "1.2.643.7.1.1.1.1":
                digestAlgorithm = "1.2.643.7.1.1.2.2";
                break;
            case "1.2.643.7.1.1.1.2":
                digestAlgorithm = "1.2.643.7.1.1.2.3";
                break;
            default:
                throw new FatalError();
        }

        return digestAlgorithm;
    }

    private String getSignatureAlgorithm(PublicKey publicKey) throws IOException {
        PublicKeyInfo publicKeyInfo = new PublicKeyInfo();
        publicKeyInfo.decode(publicKey.getEncoded());

        String algorithm = OID.DERToOID(publicKeyInfo.algorithmIdentifier.algorithm.getContent());

        String signatureAlgorithm;

        switch (algorithm) {
            case "1.2.643.2.2.19":
                signatureAlgorithm = JCP.RAW_GOST_EL_SIGN_NAME;
                break;
            case "1.2.643.7.1.1.1.1":
                signatureAlgorithm = JCP.RAW_GOST_SIGN_2012_256_NAME;
                break;
            case "1.2.643.7.1.1.1.2":
                signatureAlgorithm = JCP.RAW_GOST_SIGN_2012_512_NAME;
                break;
            default:
                throw new FatalError();
        }

        return signatureAlgorithm;
    }

    private MethodResponse<String> sign(String uuid, String password, String base64Data) {
        try {
            KeyStore keyStorePFX = KeyStore.getInstance(JCSP.PFX_STORE_NAME, JCSP.PROVIDER_NAME);
            InputStream fileInputStream = new FileInputStream(context.getFilesDir().getParent() + "/app_flutter/certificates/" + uuid + ".pfx");

            keyStorePFX.load(fileInputStream, password.toCharArray());

            String alias = null;
            Enumeration<String> aliasesPFX = keyStorePFX.aliases();

            while (aliasesPFX.hasMoreElements()) {
                String aliasPFX = aliasesPFX.nextElement();
                log.info(aliasPFX);
                if (keyStorePFX.isKeyEntry(aliasPFX))
                    alias = aliasPFX;
            }

            if (alias != null) {
                X509Certificate certificate = (X509Certificate) keyStorePFX.getCertificate(alias);

                log.info("Данные " + base64Data);
                byte[] data = Base64.decode(base64Data, Base64.DEFAULT);

                log.info(certificate.getPublicKey().getAlgorithm());

                MessageDigest md = MessageDigest.getInstance(
                        getDigestAlgorithm(certificate.getPublicKey()),
                        JCSP.PROVIDER_NAME
                );
                md.update(data);
                byte[] digest = md.digest();

                log.info("Хэш " + Arrays.toString(digest));

                log.info("Сертификат распакован");
                PrivateKey privateKey = (PrivateKey) keyStorePFX.getKey(alias, password.toCharArray());

                Signature signature = Signature.getInstance(getSignatureAlgorithm(certificate.getPublicKey()), JCSP.PROVIDER_NAME);
                signature.initSign(privateKey);
                signature.update(digest);
                byte[] sign = signature.sign();

                JSONObject contentJson = new JSONObject();
                contentJson.put("sign-data", base64Data);
                contentJson.put("serialNumber", certificate.getSerialNumber().toString());
                contentJson.put("certificate", Base64.encodeToString(certificate.getEncoded(), Base64.NO_WRAP));
                contentJson.put("signature", Base64.encodeToString(sign, Base64.NO_WRAP));

                return new MethodResponse<String>(contentJson.toString(), MethodResponseCode.SUCCESS);
            } else {
                log.info("Сертификат не распакован");
                throw new Exception("Ошибка при импорте *.pfx сертификата");
            }
        } catch (Exception exception) {
            log.info("Ошибка при чтении сертификата");
            StringWriter writer = new StringWriter();
            PrintWriter printWriter = new PrintWriter(writer);
            exception.printStackTrace(printWriter);
            printWriter.flush();

            String stackTrace = writer.toString();
            log.info(stackTrace);
            return new MethodResponse<String>("Ошибка: " + exception.toString(), MethodResponseCode.ERROR);
        }
    }
}

class MethodResponse<T> {
    T content;
    MethodResponseCode code;

    public MethodResponse(T content, MethodResponseCode code) {
        this.content = content;
        this.code = code;
    }
}

enum MethodResponseCode {
    SUCCESS,
    ERROR
}