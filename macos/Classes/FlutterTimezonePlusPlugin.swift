import Cocoa
import FlutterMacOS

public class FlutterTimezonePlusPlugin: NSObject, FlutterPlugin {
  public static func register(with registrar: FlutterPluginRegistrar) {
    let channel = FlutterMethodChannel(name: "flutter_timezone_plus", binaryMessenger: registrar.messenger)
    let instance = FlutterTimezonePlusPlugin()
    registrar.addMethodCallDelegate(instance, channel: channel)
  }

  public func handle(_ call: FlutterMethodCall, result: @escaping FlutterResult) {
    switch call.method {
    case "getLocalTimezone":
      result(NSTimeZone.local.identifier)
    case "getAvailableTimezones":
      result(NSTimeZone.knownTimeZoneNames)
    default:
      result(FlutterMethodNotImplemented)
    }
  }
}
