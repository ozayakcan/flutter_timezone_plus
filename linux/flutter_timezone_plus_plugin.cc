#include "include/flutter_timezone_plus/flutter_timezone_plus_plugin.h"

#include <flutter_linux/flutter_linux.h>
#include <gtk/gtk.h>
#include <sys/utsname.h>

#include <cstring>

#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>

#include <time.h>

#include "flutter_timezone_plus_plugin_private.h"

#define FLUTTER_TIMEZONE_PLUS_PLUGIN(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), flutter_timezone_plus_plugin_get_type(), \
                              FlutterTimezonePlusPlugin))

struct _FlutterTimezonePlusPlugin {
  GObject parent_instance;
};

G_DEFINE_TYPE(FlutterTimezonePlusPlugin, flutter_timezone_plus_plugin, g_object_get_type())

// Called when a method call is received from Flutter.
static void flutter_timezone_plus_plugin_handle_method_call(
    FlutterTimezonePlusPlugin* self,
    FlMethodCall* method_call) {
  g_autoptr(FlMethodResponse) response = nullptr;

  const gchar* method = fl_method_call_get_name(method_call);

  if (strcmp(method, "getLocalTimezone") == 0) {
    response = get_local_timezone();
  }else if (strcmp(method, "getAvailableTimezones") == 0) {
    response = get_available_timezones();
  } else {
    response = FL_METHOD_RESPONSE(fl_method_not_implemented_response_new());
  }

  fl_method_call_respond(method_call, response, nullptr);
}

FlMethodResponse* get_local_timezone() {
  char tz[128];
  if (findDefaultTZ(tz, sizeof(tz))){
    g_autofree gchar *ltz = g_strdup_printf("%s", tz);
    g_autoptr(FlValue) mtz = fl_value_new_string(ltz);
    return FL_METHOD_RESPONSE(fl_method_success_response_new(mtz));
  }else{
    return FL_METHOD_RESPONSE(fl_method_success_response_new(nullptr));
  }
}
FlMethodResponse* get_available_timezones() {
  char tz[128];
  FlValue* out = fl_value_new_list();
  
  FILE *fp;
  char path[1035];

  /* Open the command for reading. */
  fp = popen("timedatectl list-timezones", "r");
  if (fp == NULL) {
    if (findDefaultTZ(tz, sizeof(tz))){
      g_autofree gchar *ltz = g_strdup_printf("%s", tz);
      fl_value_append_take(out, fl_value_new_string(ltz));
    }
  }else{
    while (fgets(path, sizeof(path), fp) != NULL) {
      g_autofree gchar *ltz = g_strdup_printf("%s", trim(path));
      fl_value_append_take(out, fl_value_new_string(ltz));
    }
    /* close */
    pclose(fp);
  }
  
  return FL_METHOD_RESPONSE(fl_method_success_response_new(out));
}

char *findDefaultTZ(char *tz, size_t tzSize)
{
  char *ret = NULL;
  /* If there is an /etc/timezone file, then we expect it to contain
   * nothing except the timezone. */
  FILE *fd = fopen("/etc/timezone", "r"); /* Ubuntu. */
  if (fd)
  {
    char buffer[128];
    /* There should only be one line, in this case. */
    while (fgets(buffer, sizeof(buffer), fd))
    {
      char *lasts = buffer;
      /* We don't want a line feed on the end. */
      char *tag = strtok_r(lasts, " \t\n", &lasts);
      /* Idiot check. */
      if (tag && strlen(tag) > 0 && tag[0] != '#')
      {
        strncpy(tz, tag, tzSize);
        ret = tz;
        
      }
    }
    fclose(fd);
  }
  else if (getValue((char *)"/etc/sysconfig/clock", (char *)"ZONE", tz, tzSize)) /* Redhat.    */
    ret = tz;
  else if (getValue((char *)"/etc/TIMEZONE", (char *)"TZ", tz, tzSize))     /* Solaris. */
    ret = tz;
  return ret;
}

/* Look for tag=someValue within filename.  When found, return someValue
 * in the provided value parameter up to valueSize in length.  If someValue
 * is enclosed in quotes, remove them. */
char *getValue(char *filename, char *tag, char *value, size_t valueSize)
{
  char buffer[128], *lasts;
  int foundTag = 0;

  FILE *fd = fopen(filename, "r");
  if (fd)
  {
    /* Process the file, line by line. */
    while (fgets(buffer, sizeof(buffer), fd))
    {
      lasts = buffer;
      /* Look for lines with tag=value. */
      char *token = strtok_r(lasts, "=", &lasts);
      /* Is this the tag we are looking for? */
      if (token && !strcmp(token, tag))
      {
        /* Parse out the value. */
        char *zone = strtok_r(lasts, " \t\n", &lasts);
        /* If everything looks good, copy it to our return var. */
        if (zone && strlen(zone) > 0)
        {
          int i = 0;
          int j = 0;
          char quote = 0x00;
          /* Rather than just simple copy, remove quotes while we copy. */
          for (i = 0; i < strlen(zone) && i < valueSize - 1; i++)
          {
            /* Start quote. */
            if (quote == 0x00 && zone[i] == '"')
              quote = zone[i];
            /* End quote. */
            else if (quote != 0x00 && quote == zone[i])
              quote = 0x00;
            /* Copy bytes. */
            else
            {
              value[j] = zone[i];
              j++;
            }
          }
          value[j] = 0x00;
          foundTag = 1;
        }
        break;
      }
    }
    fclose(fd);
  }
  if (foundTag)
    return value;
  return NULL;
}

char *trim(char *string)
{
    char *ptr = NULL;
    while (*string == ' ' || *string == '\n') string++;  // chomp away space and new line at the start
    ptr = string + strlen(string) - 1; // jump to the last char (-1 because '\0')
    while (*ptr == ' ' || *ptr == '\n'){ *ptr = '\0' ; ptr--; } ; // overwrite with end of string
    return string;  // return pointer to the modified start 
}

static void flutter_timezone_plus_plugin_dispose(GObject* object) {
  G_OBJECT_CLASS(flutter_timezone_plus_plugin_parent_class)->dispose(object);
}

static void flutter_timezone_plus_plugin_class_init(FlutterTimezonePlusPluginClass* klass) {
  G_OBJECT_CLASS(klass)->dispose = flutter_timezone_plus_plugin_dispose;
}

static void flutter_timezone_plus_plugin_init(FlutterTimezonePlusPlugin* self) {}

static void method_call_cb(FlMethodChannel* channel, FlMethodCall* method_call,
                           gpointer user_data) {
  FlutterTimezonePlusPlugin* plugin = FLUTTER_TIMEZONE_PLUS_PLUGIN(user_data);
  flutter_timezone_plus_plugin_handle_method_call(plugin, method_call);
}

void flutter_timezone_plus_plugin_register_with_registrar(FlPluginRegistrar* registrar) {
  FlutterTimezonePlusPlugin* plugin = FLUTTER_TIMEZONE_PLUS_PLUGIN(
      g_object_new(flutter_timezone_plus_plugin_get_type(), nullptr));

  g_autoptr(FlStandardMethodCodec) codec = fl_standard_method_codec_new();
  g_autoptr(FlMethodChannel) channel =
      fl_method_channel_new(fl_plugin_registrar_get_messenger(registrar),
                            "flutter_timezone_plus",
                            FL_METHOD_CODEC(codec));
  fl_method_channel_set_method_call_handler(channel, method_call_cb,
                                            g_object_ref(plugin),
                                            g_object_unref);

  g_object_unref(plugin);
}
