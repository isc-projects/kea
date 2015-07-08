{
  "module_spec": {
    "module_name": "Logging",
    "module_description": "Logging configuration",
    "config_data": [
      {
        "item_name": "loggers",
        "item_type": "list",
        "item_optional": false,
        "item_default": [],
        "list_item_spec":
        {
          "item_name": "logger",
          "item_type": "map",
          "item_optional": false,
          "item_default": {},
          "map_item_spec": [
          {
            "item_name": "name",
            "item_type": "string",
            "item_optional": false,
            "item_default": "kea",
            "item_description": "Logging name"
          },

          {
            "item_name": "output_options",
            "item_type": "list",
            "item_optional": true,
            "item_default": [],
            "list_item_spec":
            {
               "item_name": "output_option",
               "item_type": "map",
               "item_optional": false,
               "item_default": {},
               "item_description": "Options for a logging destination",
               "map_item_spec": [
               {
                 "item_name": "output",
                 "item_type": "string",
                 "item_optional": false,
                 "item_default": "stdout",
                 "item_description": "Logging destination (stdout, stderr, syslog, syslog:name, file name)"
               },

               {
                 "item_name": "maxver",
                 "item_type": "integer",
                 "item_optional": true,
                 "item_default": 1,
                 "item_description": "Maximum number of log files in rotation"
               },

               {
                 "item_name": "maxsize",
                 "item_type": "integer",
                 "item_optional": true,
                 "item_default": 204800,
                 "item_description": "Maximum log file size"
               },

               {
                 "item_name": "flush",
                 "item_type": "boolean",
                 "item_optional": true,
                 "item_default": true,
                 "item_description": "Immediate flush"
               }
               ]
             }
          },

          {
            "item_name": "severity",
            "item_type": "string",
            "item_optional": false,
            "item_default": "INFO",
            "item_description": "Logging severity"
          },

          {
            "item_name": "debuglevel",
            "item_type": "integer",
            "item_optional": true,
            "item_default": 0,
            "item_description": "Debug level (for DEBUG severity, 0..99 range)"
          }
          ]
        }
      }
    ]
  }
}
