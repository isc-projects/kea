{
  "module_spec": {
    "module_name": "DDNS",
    "config_data": [
      {
        "item_name": "zones",
        "item_type": "list",
        "item_optional": false,
        "item_default": [],
        "list_item_spec": {
          "item_name": "entry",
          "item_type": "map",
          "item_optional": true,
          "item_default": {
          "origin": "",
          "class": "IN",
            "update_acl": []
          },
          "map_item_spec": [
            {
              "item_name": "origin",
              "item_type": "string",
              "item_optional": false,
              "item_default": ""
            },
            {
              "item_name": "class",
              "item_type": "string",
              "item_optional": false,
              "item_default": "IN"
            },
            {
              "item_name": "update_acl",
              "item_type": "list",
              "item_optional": false,
              "item_default": [],
              "list_item_spec": {
                "item_name": "acl_element",
                "item_type": "any",
                "item_optional": true,
                "item_default": {"action": "REJECT"}
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

