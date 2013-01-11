{
  "module_spec": {
    "module_name": "Dhcp6",
    "module_description": "DHCPv6 server daemon",
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

      { "item_name": "preferred-lifetime",
        "item_type": "integer",
        "item_optional": false,
        "item_default": 3000
      },

      { "item_name": "valid-lifetime",
        "item_type": "integer",
        "item_optional": false,
        "item_default": 4000
      },

      { "item_name": "option-def",
        "item_type": "list",
        "item_optional": false,
        "item_default": [],
        "list_item_spec":
        {
          "item_name": "single-option-def",
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
            "item_default": 0,
          },

          { "item_name": "type",
            "item_type": "string",
            "item_optional": false,
            "item_default": "",
          },

          { "item_name": "array",
            "item_type": "boolean",
            "item_optional": false,
            "item_default": False
          },

          { "item_name": "record_types",
            "item_type": "string",
            "item_optional": false,
            "item_default": "",
          },

          { "item_name": "space",
            "item_type": "string",
            "item_optional": false,
            "item_default": ""
          },

          { "item_name": "encapsulate",
            "item_type": "string",
            "item_optional": false,
            "item_default": ""
          } ]
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

          { "item_name": "code",
            "item_type": "integer",
            "item_optional": false,
            "item_default": 0
          },
          { "item_name": "data",
            "item_type": "string",
            "item_optional": false,
            "item_default": ""
          },
          { "item_name": "csv-format",
            "item_type": "boolean",
            "item_optional": false,
            "item_default": False
          },
          { "item_name": "space",
            "item_type": "string",
            "item_optional": false,
            "item_default": "dhcp6"
          } ]
        }
      },

      { "item_name": "subnet6",
        "item_type": "list",
        "item_optional": false,
        "item_default": [],
        "list_item_spec":
        {
            "item_name": "single-subnet6",
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

                { "item_name": "preferred-lifetime",
                  "item_type": "integer",
                  "item_optional": false,
                  "item_default": 3000
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
                    },
                    { "item_name": "csv-format",
                      "item_type": "boolean",
                      "item_optional": false,
                      "item_default": False
                    },
                    { "item_name": "space",
                      "item_type": "string",
                      "item_optional": false,
                      "item_default": "dhcp6"
                    } ]
                  }
                } ]
            }
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
