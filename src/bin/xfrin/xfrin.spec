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
          },
          { "item_name": "use_ixfr",
            "item_type": "boolean",
            "item_optional": false,
            "item_default": false
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
        "command_args": [
          {
            "item_name": "pid",
            "item_type": "integer",
            "item_optional": true
          }
        ]
      }
    ],
    "statistics": [
      {
        "item_name": "zones",
        "item_type": "named_set",
        "item_optional": false,
        "item_default": {
          "_SERVER_" : {
	    "soaoutv4": 0,
	    "soaoutv6": 0,
	    "axfrreqv4": 0,
	    "axfrreqv6": 0,
	    "ixfrreqv4": 0,
	    "ixfrreqv6": 0,
	    "xfrsuccess": 0,
	    "xfrfail": 0,
	    "time_to_ixfr": 0.0,
	    "time_to_axfr": 0.0
          }
        },
        "item_title": "Zone names",
        "item_description": "Zone names for Xfrout statistics",
        "named_set_item_spec": {
          "item_name": "zonename",
          "item_type": "map",
          "item_optional": false,
          "item_default": {},
          "item_title": "Zone name",
          "item_description": "Zone name for Xfrout statistics",
          "map_item_spec": [
            {
              "item_name": "soaoutv4",
              "item_type": "integer",
              "item_optional": false,
              "item_default": 0,
              "item_title": "SOAOutv4",
              "item_description": "Number of IPv4 SOA queries sent from Xfrin"
            },
            {
              "item_name": "soaoutv6",
              "item_type": "integer",
              "item_optional": false,
              "item_default": 0,
              "item_title": "SOAOutv6",
              "item_description": "Number of IPv6 SOA queries sent from Xfrin"
            },
            {
              "item_name": "axfrreqv4",
              "item_type": "integer",
              "item_optional": false,
              "item_default": 0,
              "item_title": "AXFRReqv4",
              "item_description": "Number of IPv4 AXFR requests sent from Xfrin"
            },
            {
              "item_name": "axfrreqv6",
              "item_type": "integer",
              "item_optional": false,
              "item_default": 0,
              "item_title": "AXFRReqv6",
              "item_description": "Number of IPv6 AXFR requests sent from Xfrin"
            },
            {
              "item_name": "ixfrreqv4",
              "item_type": "integer",
              "item_optional": false,
              "item_default": 0,
              "item_title": "IXFRReqv4",
              "item_description": "Number of IPv4 IXFR requests sent from Xfrin"
            },
            {
              "item_name": "ixfrreqv6",
              "item_type": "integer",
              "item_optional": false,
              "item_default": 0,
              "item_title": "IXFRReqv6",
              "item_description": "Number of IPv6 IXFR requests sent from Xfrin"
            },
            {
              "item_name": "xfrsuccess",
              "item_type": "integer",
              "item_optional": false,
              "item_default": 0,
              "item_title": "XfrSuccess",
              "item_description": "Number of zone transfer requests succeeded"
            },
            {
              "item_name": "xfrfail",
              "item_type": "integer",
              "item_optional": false,
              "item_default": 0,
              "item_title": "XfrFail",
              "item_description": "Number of zone transfer requests failed"
            },
            {
              "item_name": "time_to_ixfr",
              "item_type": "real",
              "item_optional": false,
              "item_default": 0.0,
              "item_title": "Time to IXFR",
              "item_description": "Elapsed time in seconds to do the last IXFR"
            },
            {
              "item_name": "time_to_axfr",
              "item_type": "real",
              "item_optional": false,
              "item_default": 0.0,
              "item_title": "Time to AXFR",
              "item_description": "Elapsed time in seconds to do the last AXFR"
            }
          ]
        }
      }
    ]
  }
}
