// ignore_for_file: library_private_types_in_public_api

import 'dart:async';

import 'package:flutter/services.dart';
import 'package:flutter_web_plugins/flutter_web_plugins.dart';
import 'package:js/js.dart';

///
/// The plugin class for the web, acts as the plugin inside bits
/// and connects to the js world.
///
class FlutterTimezonePlugin {
  static void registerWith(Registrar registrar) {
    final MethodChannel channel = MethodChannel(
      'flutter_timezone_plus',
      const StandardMethodCodec(),
      registrar,
    );
    final FlutterTimezonePlugin instance = FlutterTimezonePlugin();
    channel.setMethodCallHandler(instance.handleMethodCall);
  }

  Future<dynamic> handleMethodCall(MethodCall call) async {
    switch (call.method) {
      case 'getLocalTimezone':
        return _getLocalTimeZone();
      case 'getAvailableTimezones':
        return [_getLocalTimeZone()];
      default:
        throw PlatformException(
            code: 'Unimplemented',
            details:
                "The flutter_native_timezone plugin for web doesn't implement "
                "the method '${call.method}'");
    }
  }

  /// Platform-specific implementation of determining the user's
  /// local time zone when running on the web.
  ///
  String _getLocalTimeZone() {
    return jsDateTimeFormat().resolvedOptions().timeZone;
  }
}

@JS('Intl.DateTimeFormat')
external _JSDateTimeFormat jsDateTimeFormat();

@JS()
abstract class _JSDateTimeFormat {
  @JS()
  external _JSResolvedOptions resolvedOptions();
}

@JS()
abstract class _JSResolvedOptions {
  @JS()
  external String get timeZone;
}
