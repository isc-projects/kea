{
  "module_spec": {
    "module_name": "Dhcp4",
    "module_description": "DHCPv4 server daemon",
    "config_data": [
      { "item_name": "interface",
        "item_type": "list",
        "item_optional": false,
        "item_default": [ "all" ],
        "list_item_spec":
        {
          "item_name": "interface_name",
          "item_type": "string",
          "item_optional": false,
          "item_default": "all"
        }
      } ,

      { "item_name": "renew-timer",
        "item_type": "integer",
        "item_optional": false,
        "item_default": 1000
      },

      { "item_name": "rebind-timer",
        "item_type": "integer",
        "item_optional": false,
        "item_default": 2000
      },

      { "item_name": "valid-lifetime",
        "item_type": "integer",
        "item_optional": false,
        "item_default": 4000
      },

      { "item_name": "option-data",
        "item_type": "list",
        "item_optional": false,
        "item_default": [],
        "list_item_spec":
        {
          "item_name": "single-option-data",
          "item_type": "map",
          "item_optional": false,
          "item_default": {},
          "map_item_spec": [
          {
            "item_name": "name",
            "item_type": "string",
            "item_optional": false,
            "item_default": ""
          },

          { "item_name": "code",
            "item_type": "integer",
            "item_optional": false,
            "item_default": 0
          },
          { "item_name": "data",
            "item_type": "string",
            "item_optional": false,
            "item_default": ""
          } ]
        }
      },

      { "item_name": "subnet4",
        "item_type": "list",
        "item_optional": false,
        "item_default": [],
        "list_item_spec":
        {
            "item_name": "single-subnet4",
            "item_type": "map",
            "item_optional": false,
            "item_default": {},
            "map_item_spec": [

                { "item_name": "subnet",
                  "item_type": "string",
                  "item_optional": false,
                  "item_default": ""
                },

                { "item_name": "renew-timer",
                  "item_type": "integer",
                  "item_optional": false,
                  "item_default": 1000
                },

                { "item_name": "rebind-timer",
                  "item_type": "integer",
                  "item_optional": false,
                  "item_default": 2000
                },

                { "item_name": "valid-lifetime",
                  "item_type": "integer",
                  "item_optional": false,
                  "item_default": 7200
                },
                { "item_name": "pool",
                  "item_type": "list",
                  "item_optional": false,
                  "item_default": [],
                    "list_item_spec":
                    {
                        "item_name": "type",
                        "item_type": "string",
                        "item_optional": false,
                        "item_default": ""
                    }
                },

                { "item_name": "option-data",
                  "item_type": "list",
                  "item_optional": false,
                  "item_default": [],
                  "list_item_spec":
                  {
                    "item_name": "single-option-data",
                    "item_type": "map",
                    "item_optional": false,
                    "item_default": {},
                    "map_item_spec": [
                    {
                      "item_name": "name",
                      "item_type": "string",
                      "item_optional": false,
                      "item_default": ""
                    },
                    {
                      "item_name": "code",
                      "item_type": "integer",
                      "item_optional": false,
                      "item_default": 0
                    },
                    {
                      "item_name": "data",
                      "item_type": "string",
                      "item_optional": false,
                      "item_default": ""
                    } ]
                  }
                } ]
         }
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
