import Flutter
import UIKit

public class SwiftCryptSignaturePlugin: NSObject, FlutterPlugin {
    private let INIT_CSP_OK = 0;
    private let INIT_CSP_ERROR = -1;
    
    public static func register(with registrar: FlutterPluginRegistrar) {
        let channel = FlutterMethodChannel(name: "crypt_signature", binaryMessenger: registrar.messenger())
        let instance = SwiftCryptSignaturePlugin()
        registrar.addMethodCallDelegate(instance, channel: channel)
    }
    
    public func handle(_ call: FlutterMethodCall, result: @escaping FlutterResult) {
        let args = call.arguments as? Dictionary<String, String>;
        
        if (call.method == "initCSP") {
            let resultCode = initCSP();
            
            if (resultCode == INIT_CSP_OK) {
                result(INIT_CSP_OK);
            }
            else {
                result(FlutterError(code: "ERROR", message: "Ошибка при инициализации провайдера", details: INIT_CSP_ERROR));
            }
        }
        
        if (call.method == "installCertificate") {
            let path = args?["pathToCert"];
            let password = args?["password"];
            
            let resulty = addCert(path, password);
            
            if (resulty == nil) {
                result(FlutterError(code: "ERROR", message: "Не удалось добавить сертификат", details: nil));
            } else {
                result(resulty);
            }
        }
        
        if (call.method == "sign") {
            let alias = args?["id"];
            let password = args?["password"];
            let data = args?["data"];
            
            let resulty = sign(alias, password, data);
            
            if (resulty == nil) {
                result(FlutterError(code: "ERROR", message: "Не удалось подписать данные", details: nil));
            } else {
                result(resulty);
            }
        }
        
        result(FlutterMethodNotImplemented);
    }
}
