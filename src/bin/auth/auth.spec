{
  "data_specification": {
    "module_name": "Auth",
    "config_data": [
      { "item_name": "default_name",
        "item_type": "string",
        "item_optional": False,
        "item_default": "Hello, world!"
      },
      { "item_name": "zone_list",
        "item_type": "list",
        "item_optional": False,
        "item_default": [],
        "list_item_spec":
          { "item_name": "zone_name",
            "item_type": "string",
            "item_optional": True,
            "item_default": ""
          }
      }
    ],
    "commands": [
      {
        "command_name": "print_message",
        "command_description": "Print the given message to stdout",
        "command_args": [ {
          "item_name": "message",
          "item_type": "string",
          "item_optional": False,
          "item_default": ""
        } ]
      },
      {
        "command_name": "shutdown",
        "command_description": "Shut down BIND 10",
        "command_args": []
      }
    ]
  }
}

