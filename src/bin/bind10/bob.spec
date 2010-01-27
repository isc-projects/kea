{
  "data_specification": {
    "module_name": "Boss",
    "config_data": [
      {
        "item_name": "some_string",
        "item_type": "string",
        "item_optional": False,
        "item_default": "Hi, shane!"
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
      }
    ]
  }
}


