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
        "item_name": "start_resolver",
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
    ]
  }
}


