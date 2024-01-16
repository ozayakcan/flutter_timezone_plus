#include <flutter_linux/flutter_linux.h>

#include "include/flutter_timezone_plus/flutter_timezone_plus_plugin.h"

// This file exposes some plugin internals for unit testing. See
// https://github.com/flutter/flutter/issues/88724 for current limitations
// in the unit-testable API.

// Handles the getPlatformVersion method call.
FlMethodResponse *get_local_timezone();
FlMethodResponse *get_available_timezones();
char *findDefaultTZ(char *tz, size_t tzSize);
char *getValue(char *filename, char *tag, char *value, size_t valueSize);
char *trim(char *string);