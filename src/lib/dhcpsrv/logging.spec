{
  "module_spec": {
    "module_name": "Logging",
    "module_description": "Logging configuration",
    "config_data": [
      {
        "item_name": "loggers",
        "item_type": "list",
        "item_optional": true,
        "item_default": [],
        "list_item_spec":
        {
          "item_name": "logger-config",
          "item_type": "map",
          "item_optional": true,
          "item_default": {},
          "map_item_spec": [
          {
            "item_name": "name",
            "item_type": "string",
            "item_optional": false,
            "item_default": "kea"
          },

          {
            "item_name": "output_options",
            "item_type": "map",
            "item_optional": true,
            "item_default": {},
            "map_item_spec": [
            {
              "item_name": "output",
              "item_type": "string",
              "item_optional": false,
              "item_default": "stdout"
            },

            {
              "item_name": "maxver",
              "item_type": "integer",
              "item_optional": true,
              "item_default": 1
            },

            {
              "item_name": "maxsize",
              "item_type": "integer",
              "item_optional": true,
              "item_default": 204800
            }
            ]
          },

          {
            "item_name": "severity",
            "item_type": "string",
            "item_optional": false,
            "item_default": "INFO"
          },

          {
            "item_name": "debuglevel",
            "item_type": "integer",
            "item_optional": true,
            "item_default": 0
          }
          ]
        }
      }
    ]
  }
}
