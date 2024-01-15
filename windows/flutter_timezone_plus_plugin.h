#ifndef FLUTTER_PLUGIN_FLUTTER_TIMEZONE_PLUS_PLUGIN_H_
#define FLUTTER_PLUGIN_FLUTTER_TIMEZONE_PLUS_PLUGIN_H_

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>
#include <flutter/standard_method_codec.h>

#include <memory>

namespace flutter_timezone_plus {

class FlutterTimezonePlusPlugin : public flutter::Plugin {
 public:
  static void RegisterWithRegistrar(flutter::PluginRegistrarWindows *registrar);

  FlutterTimezonePlusPlugin();

  virtual ~FlutterTimezonePlusPlugin();

  // Disallow copy and assign.
  FlutterTimezonePlusPlugin(const FlutterTimezonePlusPlugin&) = delete;
  FlutterTimezonePlusPlugin& operator=(const FlutterTimezonePlusPlugin&) = delete;

  // Called when a method is called on this plugin's channel from Dart.
  void HandleMethodCall(
      const flutter::MethodCall<flutter::EncodableValue> &method_call,
      std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
  
};
class TimeZones
{
    public:
        static std::string Standart();
        static std::string CountryCode();
        static std::string IANA();
        static flutter::EncodableList GetAll();
        static std::string xmlTimezones;
};
}  // namespace flutter_timezone_plus

#endif  // FLUTTER_PLUGIN_FLUTTER_TIMEZONE_PLUS_PLUGIN_H_
