package ru.krista.crypt;

import android.content.Context;
import android.util.Base64;

import androidx.annotation.NonNull;

import org.apache.commons.codec.binary.Hex;
import org.json.JSONObject;

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
    private Context context;
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
                try {
                    boolean response = CryptSignature.getInstance().initCSP(context);
                    result.success(response);
                } catch (Exception e) {
                    result.error("initCSP", "Ошибка при инициализации провайдера", e);
                }
                break;
            }
            case "addCertificate": {
                try {
                    String path = call.argument("path");
                    String password = call.argument("password");
                    JSONObject response = CryptSignature.getInstance().addCertificate(path, password);
                    result.success(response.toString());
                } catch (Exception e) {
                    result.error("addCertificate", "Ошибка при добавлении сертификата", e);
                }
                break;
            }
            case "setLicense": {
                try {
                    String license = call.argument("license");
                    JSONObject response = CryptSignature.getInstance().setLicense(license);
                    result.success(response.toString());
                } catch (Exception e) {
                    result.error("setLicense", "Ошибка при установке лицезнии", e);
                }
                break;
            }
            case "getLicense": {
                try {
                    JSONObject response = CryptSignature.getInstance().getLicense();
                    result.success(response.toString());
                } catch (Exception e) {
                    result.error("getLicense", "Ошибка при получении лицезнии", e);
                }
                break;
            }
            case "digest": {
                try {
                    String certificateUUID = call.argument("certificateUUID");
                    String password = call.argument("password");
                    String message = call.argument("message");
                    JSONObject response = CryptSignature.getInstance().digest(certificateUUID, password, message, context);
                    result.success(response.toString());
                } catch (Exception e) {
                    result.error("digest", "Ошибка при расчете хэша", e);
                }
                break;
            }
            case "sign": {
                try {
                    String certificateUUID = call.argument("certificateUUID");
                    String password = call.argument("password");
                    String digest = call.argument("digest");
                    JSONObject response = CryptSignature.getInstance().sign(certificateUUID, password, digest, context);
                    result.success(response.toString());
                } catch (Exception e) {
                    result.error("sign", "Ошибка при выполнении подписи", e);
                }
                break;
            }
            case "createPKCS7": {
                try {
                    String certificateUUID = call.argument("certificateUUID");
                    String password = call.argument("password");
                    String digest = call.argument("digest");
                    JSONObject response = CryptSignature.getInstance().createPKCS7(certificateUUID, password, digest, context);
                    result.success(response.toString());
                } catch (Exception e) {
                    result.error("createPKCS7", "Ошибка при создании PKCS7", e);
                }
                break;
            }
            case "addSignatureToPKCS7": {
                try {
                    String pkcs7 = call.argument("pkcs7");
                    String signature = call.argument("signature");
                    JSONObject response = CryptSignature.getInstance().addSignatureToPKCS7(pkcs7, signature);
                    result.success(response.toString());
                } catch (Exception e) {
                    result.error("addSignatureToPKCS7", "Ошибка при добавлении атрибутов подписи к PKCS7", e);
                }
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
}