import Flutter
import UIKit

public class SwiftCryptSignaturePlugin: NSObject, FlutterPlugin {
    public static func register(with registrar: FlutterPluginRegistrar) {
        let channel = FlutterMethodChannel(name: "crypt_signature", binaryMessenger: registrar.messenger())
        let instance = SwiftCryptSignaturePlugin()
        registrar.addMethodCallDelegate(instance, channel: channel)
    }
    
    public func handle(_ call: FlutterMethodCall, result: @escaping FlutterResult) {
        let args = call.arguments as? Dictionary<String, String>;
        
        if (call.method == "initCSP") {
            let response = initCSP();
            result(response);
        }
        
        if (call.method == "addCertificate") {
            let path = args?["path"];
            let password = args?["password"];
            let response = addCertificate(path, password);
            result(response);
        }
        
        if (call.method == "digest") {
            let alias = args?["certificateUUID"];
            let password = args?["password"];
            let message = args?["message"];
            let response = digest(alias, password, message);
            result(response);
        }
        
        if (call.method == "sign") {
            let alias = args?["certificateUUID"];
            let password = args?["password"];
            let digest = args?["digest"];
            let response = sign(alias, password, digest);
            result(response);
        }
        
        result(FlutterMethodNotImplemented);
    }
}
