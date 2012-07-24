{
  "module_spec": {
    "module_name": "Dhcp4",
    "module_description": "DHCPv4 server daemon",
    "config_data": [
      { "item_name": "interface",
        "item_type": "string",
        "item_optional": false,
        "item_default": "eth0"
      }
    ],
    "commands": [
        {
            "command_name": "shutdown",
            "command_description": "Shuts down DHCPv4 server.",
            "command_args": [
                {
                    "item_name": "pid",
                    "item_type": "integer",
                    "item_optional": true
                }
            ]
        }
    ]
  }
}
