{
  "module_spec": {
    "module_name": "Xfrin",
    "config_data": [
      {
        "item_name": "transfers_in",
        "item_type": "integer",
        "item_optional": False,
        "item_default": 10
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
        "command_name": "print_settings",
        "command_description": "Print some_string and some_int to stdout",
        "command_args": []
      },
      {
        'command_name': 'retransfer',
        "command_description": 'retransfer a single zone without checking zone serial number',
        'command_args': [ {
            "item_name": "zone_name",
            "item_type": "string",
            "item_optional": False,
            "item_default": ""
          },
          {
            "item_name": "master",
            "item_type": "string",
            "item_optional": False,
            "item_default": ""
          },
          {
            "item_name": "port",
            "item_type": "integer",
            "item_optional": True,
            "item_default": 53
          },
          {
            "item_name": "db_file",
            "item_type": "string",
            "item_optional": True,
            "item_default": '/tmp/zone.sqlite3'
          }
        ]
      },
      {
        "command_name": "shutdown",
        "command_description": "Shut down BIND 10",
        "command_args": []
      }
    ]
  }
}


