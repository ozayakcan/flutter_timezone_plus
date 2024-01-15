#include "include/flutter_timezone_plus/flutter_timezone_plus_plugin_c_api.h"

#include <flutter/plugin_registrar_windows.h>

#include "flutter_timezone_plus_plugin.h"

void FlutterTimezonePlusPluginCApiRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar) {
  flutter_timezone_plus::FlutterTimezonePlusPlugin::RegisterWithRegistrar(
      flutter::PluginRegistrarManager::GetInstance()
          ->GetRegistrar<flutter::PluginRegistrarWindows>(registrar));
}
