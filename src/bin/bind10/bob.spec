{
  "module_spec": {
    "module_name": "Boss",
    "module_description": "Master process",
    "config_data": [
      {
        "item_name": "start_auth",
        "item_type": "boolean",
        "item_optional": false,
        "item_default": true
      },
      {
        "item_name": "start_recurse",
        "item_type": "boolean",
        "item_optional": false,
        "item_default": false
      }
    ],
    "commands": [
      {
        "command_name": "shutdown",
        "command_description": "Shut down BIND 10",
        "command_args": []
      }
    ]
  }
}


