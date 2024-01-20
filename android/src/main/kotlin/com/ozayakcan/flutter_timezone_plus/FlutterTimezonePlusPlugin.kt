package com.ozayakcan.flutter_timezone_plus

import android.os.Build
import androidx.annotation.NonNull
import io.flutter.embedding.engine.plugins.FlutterPlugin
import io.flutter.plugin.common.BinaryMessenger
import java.time.ZoneId
import io.flutter.plugin.common.MethodCall
import io.flutter.plugin.common.MethodChannel
import io.flutter.plugin.common.MethodChannel.MethodCallHandler
import io.flutter.plugin.common.MethodChannel.Result
import io.flutter.plugin.common.PluginRegistry.Registrar
import java.util.*
import kotlin.collections.ArrayList

class FlutterTimezonePlusPlugin: FlutterPlugin, MethodCallHandler {
  
  private lateinit var channel : MethodChannel

  // backward compatibility with flutter api v1
  companion object {
      @JvmStatic
      fun registerWith(registrar: Registrar) {
          val plugin = FlutterTimezonePlusPlugin()
          plugin.setupMethodChannel(registrar.messenger())
      }
  }

  override fun onAttachedToEngine(flutterPluginBinding: FlutterPlugin.FlutterPluginBinding) {
    setupMethodChannel(flutterPluginBinding.binaryMessenger)
  }

  override fun onMethodCall(call: MethodCall, result: Result) {
    if (call.method == "getLocalTimezone") {
      result.success(getLocalTimezone())
    } else if(call.method == "getAvailableTimezones"){
      result.success(getAvailableTimezones())
    } else {
      result.notImplemented()
    }
  }

  override fun onDetachedFromEngine(binding: FlutterPlugin.FlutterPluginBinding) {
    channel.setMethodCallHandler(null)
  }
  

  private fun getLocalTimezone(): String {
    return if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
      ZoneId.systemDefault().id
    } else {
      TimeZone.getDefault().id
    }
  }

  private fun getAvailableTimezones(): List<String> {
    return if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
      ZoneId.getAvailableZoneIds().toCollection(ArrayList())
    } else {
      TimeZone.getAvailableIDs().toCollection(ArrayList())
    }
  }

  private fun setupMethodChannel(messenger: BinaryMessenger) {
    channel = MethodChannel(messenger, "flutter_timezone_plus")
    channel.setMethodCallHandler(this)
  }
}
