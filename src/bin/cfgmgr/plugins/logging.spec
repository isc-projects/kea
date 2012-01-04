{
    "module_spec": {
        "module_name": "Logging",
        "module_description": "Logging options",
        "config_data": [
            {
                "item_name": "loggers",
                "item_type": "list",
                "item_optional": false,
                "item_default": [],
                "list_item_spec": {
                  "item_name": "logger",
                  "item_type": "map",
                  "item_optional": false,
                  "item_default": {},
                  "map_item_spec": [
                  {  "item_name": "name",
                     "item_type": "string",
                     "item_optional": false,
                     "item_default": ""
                  },
                  {  "item_name": "severity",
                     "item_type": "string",
                     "item_optional": false,
                     "item_default": "INFO"
                  },
                  {  "item_name": "debuglevel",
                     "item_type": "integer",
                     "item_optional": false,
                     "item_default": 0
                  },
                  {  "item_name": "additive",
                     "item_type": "boolean",
                     "item_optional": false,
                     "item_default": false
                  },
                  { "item_name": "output_options",
                    "item_type": "list",
                    "item_optional": false,
                    "item_default": [],
                    "list_item_spec": {
                      "item_name": "output_option",
                      "item_type": "map",
                      "item_optional": false,
                      "item_default": {},
                      "map_item_spec": [
                      { "item_name": "destination",
                        "item_type": "string",
                        "item_optional": false,
                        "item_default": "console"
                      },
                      { "item_name": "output",
                        "item_type": "string",
                        "item_optional": false,
                        "item_default": "stdout"
                      },
                      { "item_name": "flush",
                        "item_type": "boolean",
                        "item_optional": false,
                        "item_default": true
                      },
                      { "item_name": "maxsize",
                        "item_type": "integer",
                        "item_optional": false,
                        "item_default": 0
                      },
                      { "item_name": "maxver",
                        "item_type": "integer",
                        "item_optional": false,
                        "item_default": 0
                      }
                      ]
                    }
                  }
                  ]
                }
            }
        ],
        "commands": []
    }
}
