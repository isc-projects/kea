{
  "module_spec": {
    "module_name": "Cmdctl",
    "config_data": [
      {
        "item_name": "key_file",
        "item_type": "string",
        "item_optional": False,
        "item_default": 'cmdctl-keyfile.pem'
      },
      {
        "item_name": "cert_file",
        "item_type": "string",
        "item_optional": False,
        "item_default": 'cmdctl-certfile.pem'
      },
      {
        "item_name": "accounts_file",
        "item_type": "string",
        "item_optional": False,
        "item_default": 'cmdctl-accounts.csv'
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
        "command_name": "shutdown",
        "command_description": "Shut down cmdctl",
        "command_args": []
      }
    ]
  }
}


