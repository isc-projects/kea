{
  "module_spec": {
    "module_name": "Dhcp6",
    "module_description": "DHCPv6 server daemon",
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
            "command_description": "Shuts down DHCPv6 server.",
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
