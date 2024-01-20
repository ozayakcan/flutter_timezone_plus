#import "FlutterTimezonePlusPlugin.h"

@implementation FlutterTimezonePlusPlugin
+ (void)registerWithRegistrar:(NSObject<FlutterPluginRegistrar>*)registrar {
  FlutterMethodChannel* channel = [FlutterMethodChannel
      methodChannelWithName:@"flutter_timezone_plus"
            binaryMessenger:[registrar messenger]];
  FlutterTimezonePlusPlugin* instance = [[FlutterTimezonePlusPlugin alloc] init];
  [registrar addMethodCallDelegate:instance channel:channel];
}

- (void)handleMethodCall:(FlutterMethodCall*)call result:(FlutterResult)result {
  if ([@"getLocalTimezone" isEqualToString:call.method]) {
    NSTimeZone *timeZone = [NSTimeZone localTimeZone];
    NSString *tzName = [timeZone name];
    result(tzName);
  } else if([@"getAvailableTimezones" isEqualToString:call.method]) {
      result([NSTimeZone knownTimeZoneNames]);
  }
  else {
    result(FlutterMethodNotImplemented);
  }
}

@end
