{
  "module_spec": {
    "module_name": "Spec29",
    "config_data": [
      { "item_name": "item1",
        "item_type": "integer",
        "item_optional": false,
        "item_default": 1
      }
    ],
    "commands": [
      {
        "command_name": "good_command",
        "command_description": "A good command",
        "command_args": []
      },
      {
        "command_name": "bad_command",
        "command_description": "A bad command",
        "command_args": []
      },
      {
        "command_name": "command_with_arg",
        "command_description": "A command with an (integer) argument",
        "command_args": [ {
          "item_name": "number",
          "item_type": "integer",
          "item_optional": true,
          "item_default": 1
        } ]
      }
    ]
  }
}

