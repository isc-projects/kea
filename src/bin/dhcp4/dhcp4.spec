{
  "module_spec": {
    "module_name": "Dhcp4",
    "module_description": "DHCPv4 server daemon",
    "config_data": [
      {
        "item_name": "hooks-libraries",
        "item_type": "list",
        "item_optional": true,
        "item_default": [],
        "list_item_spec":
        {
          "item_name": "hooks-library-spec",
          "item_type": "map",
          "item_optional": false,
          "item_default": {},
          "map_item_spec": [
             {
                "item_name": "library",
                "item_type": "string",
                "item_optional": false,
                "item_default": ""
             }
          ]
        }
      },

      { "item_name": "interfaces-config",
        "item_type": "map",
        "item_optional": false,
        "item_default": {},
        "map_item_spec": [
        {
            "item_name": "interfaces",
            "item_type": "list",
            "item_optional": false,
            "item_default": [ "*" ],
            "list_item_spec":
            {
                "item_name": "interface_name",
                "item_type": "string",
                "item_optional": false,
                "item_default": "*"
            }
        },

        { "item_name": "dhcp-socket-type",
          "item_type": "string",
          "item_optional": true,
          "item_default": ""
        }
        ]
      },

      { "item_name": "expired-leases-processing",
        "item_type": "map",
        "item_optional": false,
        "item_default": {},
        "map_item_spec": [
        {
            "item_name": "reclaim-timer-wait-time",
            "item_type": "integer",
            "item_optional": false,
            "item_default": 10
        },
        {
            "item_name": "flush-reclaimed-timer-wait-time",
            "item_type": "integer",
            "item_optional": false,
            "item_default": 25
        },
        {
            "item_name": "hold-reclaimed-time",
            "item_type": "integer",
            "item_optional": false,
            "item_default": 3600
        },
        {
            "item_name": "max-reclaim-leases",
            "item_type": "integer",
            "item_optional": false,
            "item_default": 100
        },
        {
            "item_name": "max-reclaim-time",
            "item_type": "integer",
            "item_optional": false,
            "item_default": 250
        },
        {
            "item_name": "unwarned-reclaim-cycles",
            "item_type": "integer",
            "item_optional": false,
            "item_default": 5
        }
        ]
      },
      
      { "item_name": "renew-timer",
        "item_type": "integer",
        "item_optional": true,
        "item_default": 1000
      },

      { "item_name": "rebind-timer",
        "item_type": "integer",
        "item_optional": true,
        "item_default": 2000
      },

      { "item_name": "valid-lifetime",
        "item_type": "integer",
        "item_optional": false,
        "item_default": 4000
      },

      { "item_name": "next-server",
        "item_type": "string",
        "item_optional": true,
        "item_default": ""
      },

      { "item_name": "echo-client-id",
        "item_type": "boolean",
        "item_optional": true,
        "item_default": true
      },

      { "item_name": "match-client-id",
        "item_type": "boolean",
        "item_optional": true,
        "item_default": true
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
            "item_default": 0
          },

          { "item_name": "type",
            "item_type": "string",
            "item_optional": false,
            "item_default": ""
          },

          { "item_name": "array",
            "item_type": "boolean",
            "item_optional": false,
            "item_default": false
          },

          { "item_name": "record-types",
            "item_type": "string",
            "item_optional": false,
            "item_default": ""
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
            "item_default": false
          },
          { "item_name": "space",
            "item_type": "string",
            "item_optional": false,
            "item_default": "dhcp4"
          } ]
        }
      },

      { "item_name": "lease-database",
        "item_type": "map",
        "item_optional": false,
        "item_default": {"type": "memfile"},
        "map_item_spec": [
            {
                "item_name": "type",
                "item_type": "string",
                "item_optional": false,
                "item_default": ""
            },
            {
                "item_name": "name",
                "item_type": "string",
                "item_optional": true,
                "item_default": ""
            },
            {
                "item_name": "user",
                "item_type": "string",
                "item_optional": true,
                "item_default": ""
            },
            {
                "item_name": "host",
                "item_type": "string",
                "item_optional": true,
                "item_default": ""
            },
            {
                "item_name": "password",
                "item_type": "string",
                "item_optional": true,
                "item_default": ""
            },
            {
                "item_name": "persist",
                "item_type": "boolean",
                "item_optional": true,
                "item_default": true
            },
            {
                "item_name": "lfc-interval",
                "item_type": "integer",
                "item_optional": true,
                "item_default": 0
            }
        ]
      },
      { "item_name": "client-classes",
        "item_type": "list",
        "item_optional": true,
        "item_default": [],
        "list_item_spec":
        {
            "item_name": "client-class",
            "item_type": "map",
            "item_optional": false,
            "item_default": {},
            "map_item_spec": [
                { "item_name": "name",
                  "item_type": "string",
                  "item_optional": false,
                  "item_default": ""
                },
                { "item_name": "test",
                  "item_type": "string",
                  "item_optional": true,
                  "item_default": ""
                },
                { "item_name": "option-data",
                  "item_type": "list",
                  "item_optional": true,
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
                      "item_default": false
                      },
                    { "item_name": "space",
                      "item_type": "string",
                      "item_optional": false,
                      "item_default": "dhcp4"
                    } ]
                  }
                }
            ]
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

                { "item_name": "id",
                  "item_type": "integer",
                  "item_optional": false,
                  "item_default": 0
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

                { "item_name": "next-server",
                  "item_type": "string",
                  "item_optional": true,
                  "item_default": "0.0.0.0"
                },

                { "item_name": "match-client-id",
                  "item_type": "boolean",
                  "item_optional": true,
                  "item_default": true
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

                { "item_name": "client-class",
                  "item_type": "string",
                  "item_optional": false,
                  "item_default": "",
                  "item_description" : "Restricts access to this subnet to specified client class (if defined)"
                },

                { "item_name": "relay",
                  "item_type": "map",
                  "item_optional": false,
                  "item_default": {},
                  "item_description" : "Structure holding relay information.",
                  "map_item_spec": [
                      {
                          "item_name": "ip-address",
                          "item_type": "string",
                          "item_optional": false,
                          "item_default": "0.0.0.0",
                          "item_description" : "IPv4 address of the relay (defaults to 0.0.0.0 if not specified)."
                      }
                   ]
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
                      "item_default": false
                      },
                    { "item_name": "space",
                      "item_type": "string",
                      "item_optional": false,
                      "item_default": "dhcp4"
                    } ]
                  }
                },
                { "item_name": "reservations",
                  "item_type": "list",
                  "item_optional": false,
                  "item_default": [],
                  "list_item_spec":
                  {
                      "item_name": "reservation",
                      "item_type": "map",
                      "item_optional": false,
                      "item_default": {},
                      "map_item_spec": [
                      {
                        "item_name": "hw-address",
                        "item_type": "string",
                        "item_optional": true,
                        "item_default": ""
                      },
                      {
                        "item_name": "duid",
                        "item_type": "string",
                        "item_optional": true,
                        "item_default": ""
                      },
                      {
                        "item_name": "hostname",
                        "item_type": "string",
                        "item_optional": false,
                        "item_default": ""
                      },
                      {
                        "item_name": "ip-address",
                        "item_type": "string",
                        "item_optional": false,
                        "item_default": "0.0.0.0"
                      } ]
                  }
                },
                {
                  "item_name": "reservation-mode",
                  "item_type": "string",
                  "item_optional": true,
                  "item_default": "all",
                  "item_description": "Specifies allowed host reservation types. Disabling unused modes may improve performance. Allowed values: disabled, off, out-of-pool, all"
                }
             ]
         }
      },

      { "item_name": "dhcp-ddns",
        "item_type": "map",
        "item_optional": false,
        "item_default": {"enable-updates": false},
        "item_description" : "Contains parameters pertaining DHCP-driven DDNS updates",
        "map_item_spec": [
            {
                "item_name": "enable-updates",
                "item_type": "boolean",
                "item_optional": false,
                "item_default": false,
                "item_description" : "Enables DDNS update processing"
            },
            {
                "item_name": "server-ip",
                "item_type": "string",
                "item_optional": true,
                "item_default": "127.0.0.1",
                "item_description" : "IP address of kea-dhcp-ddns (IPv4 or IPv6)"
            },
            {
                "item_name": "server-port",
                "item_type": "integer",
                "item_optional": true,
                "item_default": 53001,
                "item_description" : "port number of kea-dhcp-ddns"
            },
            {
                "item_name": "sender-ip",
                "item_type": "string",
                "item_optional": true,
                "item_default": "",
                "item_description" : "IP address from which to send to kea-dhcp-ddns (IPv4 or IPv6)"
            },
            {
                "item_name": "sender-port",
                "item_type": "integer",
                "item_optional": true,
                "item_default": 0,
                "item_description" : "port number from which to send to kea-dhcp-ddns"
            },
            {
                "item_name": "max-queue-size",
                "item_type": "integer",
                "item_optional": true,
                "item_default": 1024,
                "item_description" : "maximum number of requests allowed in the send queue"
            },
            {
                "item_name": "ncr-protocol",
                "item_type": "string",
                "item_optional": true,
                "item_default": "UDP",
                "item_description" : "Socket protocol to use with kea-dhcp-ddns"
            },
            {
                "item_name": "ncr-format",
                "item_type": "string",
                "item_optional": true,
                "item_default": "JSON",
                "item_description" : "Format of the update request packet"
            },
            {

                "item_name": "always-include-fqdn",
                "item_type": "boolean",
                "item_optional": true,
                "item_default": false,
                "item_description": "Enable always including the FQDN option in its response"
            },
            {
                "item_name": "override-no-update",
                "item_type": "boolean",
                "item_optional": true,
                "item_default": false,
                "item_description": "Do update, even if client requested no updates with N flag"
            },
            {
                "item_name": "override-client-update",
                "item_type": "boolean",
                "item_optional": true,
                "item_default": false,
                "item_description": "Server performs an update even if client requested delegation"
            },
            {
                "item_name": "replace-client-name",
                "item_type": "boolean",
                "item_optional": true,
                "item_default": false,
                "item_description": "Should server replace the domain-name supplied by the client"
            },
            {
                "item_name": "generated-prefix",
                "item_type": "string",
                "item_optional": true,
                "item_default": "myhost",
                "item_description": "Prefix to use when generating the client's name"
            },

            {
                "item_name": "qualifying-suffix",
                "item_type": "string",
                "item_optional": true,
                "item_default": "",
                "item_description": "Fully qualified domain-name suffix if partial name provided by client"
            },
        ]
      },

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
        },

        {
            "command_name": "libreload",
            "command_description": "Reloads the current hooks libraries.",
            "command_args": []
        }

    ]
  }
}
