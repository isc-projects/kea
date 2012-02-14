{
  "module_spec": {
    "module_name": "DDNS",
    "config_data": [
      {
        "item_name": "zones",
        "item_type": "named_set",
        "item_optional": false,
        "item_default": {},
        "named_set_item_spec": {
          "item_name": "entry",
          "item_type": "map",
          "item_optional": true,
          "item_default": {
            "update_acl": [{"action": "ACCEPT", "from": "127.0.0.1"},
                           {"action": "ACCEPT", "from": "::1"}]
          },
          "map_item_spec": [
            {
              "item_name": "update_acl",
              "item_type": "list",
              "item_optional": false,
              "list_item_spec": {
                "item_name": "acl_element",
                "item_type": "any",
                "item_optional": true
              }
            }
          ]
        }
      }
    ],
    "commands": [
      {
        "command_name": "shutdown",
        "command_description": "Shut down DDNS",
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

