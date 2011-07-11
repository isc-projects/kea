{
  "module_spec": {
    "module_name": "Xfrin",
    "module_description": "XFR in daemon",
    "config_data": [
      {
        "item_name": "transfers_in",
        "item_type": "integer",
        "item_optional": false,
        "item_default": 10
      },
      { "item_name": "zones",
        "item_type": "list",
        "item_optional": false,
        "item_default": [],
        "list_item_spec":
        { "item_type": "map",
          "item_name": "zone_info",
          "item_optional": false,
          "item_default": {},
          "map_item_spec": [
          { "item_name": "name",
            "item_type": "string",
            "item_optional": false,
            "item_default": ""
          },
          { "item_name": "class",
            "item_type": "string",
            "item_optional": false,
            "item_default": "IN"
          },
          {
            "item_name": "master_addr",
            "item_type": "string",
            "item_optional": false,
            "item_default": ""
          },
          { "item_name": "master_port",
            "item_type": "integer",
            "item_optional": false,
            "item_default": 53
          },
          { "item_name": "tsig_key",
            "item_type": "string",
            "item_optional": true
          }
          ]
        }
      },
      { "item_name": "new_zones",
        "item_type": "named_map",
        "item_optional": false,
        "item_default": {},
        "named_map_item_spec": {
          "item_name": "zone",
          "item_type": "map",
          "item_default": {},
          "map_item_spec": [
          { "item_name": "class",
            "item_type": "string",
            "item_optional": false,
            "item_default": "IN"
          },
          {
            "item_name": "master_addr",
            "item_type": "string",
            "item_optional": false,
            "item_default": ""
          },
          { "item_name": "master_port",
            "item_type": "integer",
            "item_optional": false,
            "item_default": 53
          },
          { "item_name": "tsig_key",
            "item_type": "string",
            "item_optional": true
          }
          ]
        }
      }
    ],
    "commands": [
     {
        "command_name": "retransfer",
        "command_description": "retransfer a single zone without checking zone serial number",
        "command_args": [ {
            "item_name": "zone_name",
            "item_type": "string",
            "item_optional": false,
            "item_default": ""
          },
          {
            "item_name": "zone_class",
            "item_type": "string",
            "item_optional": true,
            "item_default": "IN"
          },
          {
            "item_name": "master",
            "item_type": "string",
            "item_optional": true,
            "item_default": ""
          },
          {
            "item_name": "port",
            "item_type": "integer",
            "item_optional": true,
            "item_default": 53
          }
        ]
      },
      {
        "command_name": "shutdown",
        "command_description": "Shut down xfrin module",
        "command_args": []
      }
    ]
  }
}
