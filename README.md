# flutter_timezone_plus

A fork of [flutter_timezone](https://github.com/tjarvstrand/flutter_timezone) works on windows and linux

## Usage examples

### Get the timezone

Current timezone:

```dart
// Returns null if timezone not found on windows or linux.
final String? currentTimeZone = await FlutterTimezone.getLocalTimezone();
```

All available timezones:

```dart
final List<String> availableTimezones = await FlutterTimezone.getAvailableTimezones();
```

## Reference

[Wikipedia's list of TZ database names](https://en.wikipedia.org/wiki/List_of_tz_database_time_zones)

## Credits

[https://pub.dev/packages/flutter_timezone](https://pub.dev/packages/flutter_timezone)

[https://github.com/tjarvstrand/flutter_timezone](https://github.com/tjarvstrand/flutter_timezone)
