{
  "module_spec": {
    "module_name": "Boss",
    "module_description": "Master process",
    "config_data": [
      {
        "item_name": "components",
        "item_type": "named_set",
        "item_optional": false,
        "item_default": {
          "b10-stats": { "address": "Stats", "kind": "dispensable" },
          "b10-cmdctl": { "special": "cmdctl", "kind": "needed" }
        },
        "named_set_item_spec": {
          "item_name": "component",
          "item_type": "map",
          "item_optional": false,
          "item_default": { },
          "map_item_spec": [
            {
              "item_name": "special",
              "item_optional": true,
              "item_type": "string"
            },
            {
              "item_name": "process",
              "item_optional": true,
              "item_type": "string"
            },
            {
              "item_name": "kind",
              "item_optional": false,
              "item_type": "string",
              "item_default": "dispensable"
            },
            {
              "item_name": "address",
              "item_optional": true,
              "item_type": "string"
            },
            {
              "item_name": "params",
              "item_optional": true,
              "item_type": "list",
              "list_item_spec": {
                "item_name": "param",
                "item_optional": false,
                "item_type": "string",
                "item_default": ""
              }
            },
            {
              "item_name": "priority",
              "item_optional": true,
              "item_type": "integer"
            }
          ]
        }
      }
    ],
    "commands": [
      {
        "command_name": "shutdown",
        "command_description": "Shut down BIND 10",
        "command_args": []
      },
      {
        "command_name": "ping",
        "command_description": "Ping the boss process",
        "command_args": []
      },
      {
        "command_name": "show_processes",
        "command_description": "List the running BIND 10 processes",
        "command_args": []
      }
    ],
    "statistics": [
      {
        "item_name": "boot_time",
        "item_type": "string",
        "item_optional": false,
        "item_default": "1970-01-01T00:00:00Z",
        "item_title": "Boot time",
        "item_description": "A date time when bind10 process starts initially",
        "item_format": "date-time"
      }
    ]
  }
}


