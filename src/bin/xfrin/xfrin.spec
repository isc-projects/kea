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
          },
          { "item_name": "request_ixfr",
            "item_type": "string",
            "item_optional": false,
            "item_default": "yes"
          }
          ]
        }
      }
    ],
    "commands": [
     {
        "command_name": "retransfer",
        "command_description": "retransfer a single zone without checking zone serial number, always using AXFR",
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
        "command_name": "refresh",
        "command_description": "transfer a single zone with checking zone serial number and honoring the request_ixfr policy",
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
          "IN" : {
            "_SERVER_" : {
              "soaoutv4": 0,
              "soaoutv6": 0,
              "axfrreqv4": 0,
              "axfrreqv6": 0,
              "ixfrreqv4": 0,
              "ixfrreqv6": 0,
              "xfrsuccess": 0,
              "xfrfail": 0,
              "last_ixfr_duration": 0.0,
              "last_axfr_duration": 0.0
            }
          }
        },
        "item_title": "Zone names",
        "item_description": "A directory name of per-zone statistics",
        "named_set_item_spec": {
          "item_name": "classname",
          "item_type": "named_set",
          "item_optional": false,
          "item_default": {},
          "item_title": "RR class name",
          "item_description": "An actual RR class name of the zone, e.g. IN, CH, and HS",
          "named_set_item_spec": {
            "item_name": "zonename",
            "item_type": "map",
            "item_optional": false,
            "item_default": {},
            "item_title": "Zone name",
            "item_description": "An actual zone name or special zone name _SERVER_ representing the entire server",
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
                "item_description": "Number of zone transfer requests succeeded. These include the case where the zone turns out to be the latest as a result of an initial SOA query (and there is actually no AXFR or IXFR transaction)."
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
                "item_name": "last_axfr_duration",
                "item_type": "real",
                "item_optional": false,
                "item_default": 0.0,
                "item_title": "Last AXFR duration",
                "item_description": "Duration in seconds of the last successful AXFR.  0.0 means no successful AXFR done or means a successful AXFR done in less than a microsecond.  If an AXFR is aborted due to some failure, this duration won't be updated."
              },
              {
                "item_name": "last_ixfr_duration",
                "item_type": "real",
                "item_optional": false,
                "item_default": 0.0,
                "item_title": "Last IXFR duration",
                "item_description": "Duration in seconds of the last successful IXFR.  0.0 means no successful IXFR done or means a successful IXFR done in less than a microsecond.  If an IXFR is aborted due to some failure, this duration won't be updated."
              }
            ]
          }
        }
      },
      {
        "item_name": "socket",
        "item_type": "map",
        "item_optional": false,
        "item_default": {
          "ipv4": {
            "tcp": {
              "open": 0,
              "openfail": 0,
              "close": 0,
              "connfail": 0,
              "conn": 0,
              "senderr": 0,
              "recverr": 0
            }
          },
          "ipv6": {
            "tcp": {
              "open": 0,
              "openfail": 0,
              "close": 0,
              "connfail": 0,
              "conn": 0,
              "senderr": 0,
              "recverr": 0
            }
          }
        },
        "item_title": "Socket",
        "item_description": "A directory name of socket statistics",
        "map_item_spec": [
          {
            "item_name": "ipv4",
            "item_type": "map",
            "item_optional": false,
            "item_default": {
              "tcp": {
                "open": 0,
                "openfail": 0,
                "close": 0,
                "connfail": 0,
                "conn": 0,
                "senderr": 0,
                "recverr": 0
              }
            },
            "item_title": "IPv4",
            "item_description": "A directory name of IPv4",
            "map_item_spec": [
              {
                "item_name": "tcp",
                "item_type": "map",
                "item_optional": false,
                "item_default": {
                  "open": 0,
                  "openfail": 0,
                  "close": 0,
                  "connfail": 0,
                  "conn": 0,
                  "senderr": 0,
                  "recverr": 0
                },
                "item_title": "TCP",
                "item_description": "A directory name of TCP statistics",
                "map_item_spec": [
                  {
                    "item_name": "open",
                    "item_type": "integer",
                    "item_optional": false,
                    "item_default": 0,
                    "item_title": "Open",
                    "item_description": "IPv4 TCP sockets opened successfully"
                  },
                  {
                    "item_name": "openfail",
                    "item_type": "integer",
                    "item_optional": false,
                    "item_default": 0,
                    "item_title": "Open failures",
                    "item_description": "IPv4 TCP sockets open failures"
                  },
                  {
                    "item_name": "close",
                    "item_type": "integer",
                    "item_optional": false,
                    "item_default": 0,
                    "item_title": "Close",
                    "item_description": "IPv4 TCP sockets closed"
                  },
                  {
                    "item_name": "connfail",
                    "item_type": "integer",
                    "item_optional": false,
                    "item_default": 0,
                    "item_title": "Connect failures",
                    "item_description": "IPv4 TCP sockets connection failures"
                  },
                  {
                    "item_name": "conn",
                    "item_type": "integer",
                    "item_optional": false,
                    "item_default": 0,
                    "item_title": "Connect",
                    "item_description": "IPv4 TCP connections established successfully"
                  },
                  {
                    "item_name": "senderr",
                    "item_type": "integer",
                    "item_optional": false,
                    "item_default": 0,
                    "item_title": "Send errors",
                    "item_description": "IPv4 TCP sockets send errors"
                  },
                  {
                    "item_name": "recverr",
                    "item_type": "integer",
                    "item_optional": false,
                    "item_default": 0,
                    "item_title": "Receive errors",
                    "item_description": "IPv4 TCP sockets receive errors"
                  }
                ]
              }
            ]
          },
          {
            "item_name": "ipv6",
            "item_type": "map",
            "item_optional": false,
            "item_default": {
              "tcp": {
                "open": 0,
                "openfail": 0,
                "close": 0,
                "connfail": 0,
                "conn": 0,
                "senderr": 0,
                "recverr": 0
              }
            },
            "item_title": "IPv6",
            "item_description": "A directory name of IPv6",
            "map_item_spec": [
              {
                "item_name": "tcp",
                "item_type": "map",
                "item_optional": false,
                "item_default": {
                  "open": 0,
                  "openfail": 0,
                  "close": 0,
                  "connfail": 0,
                  "conn": 0,
                  "senderr": 0,
                  "recverr": 0
                },
                "item_title": "TCP",
                "item_description": "A directory name of TCP statistics",
                "map_item_spec": [
                  {
                    "item_name": "open",
                    "item_type": "integer",
                    "item_optional": false,
                    "item_default": 0,
                    "item_title": "Open",
                    "item_description": "IPv6 TCP sockets opened successfully"
                  },
                  {
                    "item_name": "openfail",
                    "item_type": "integer",
                    "item_optional": false,
                    "item_default": 0,
                    "item_title": "Open failures",
                    "item_description": "IPv6 TCP sockets open failures"
                  },
                  {
                    "item_name": "close",
                    "item_type": "integer",
                    "item_optional": false,
                    "item_default": 0,
                    "item_title": "Close",
                    "item_description": "IPv6 TCP sockets closed"
                  },
                  {
                    "item_name": "connfail",
                    "item_type": "integer",
                    "item_optional": false,
                    "item_default": 0,
                    "item_title": "Connect failures",
                    "item_description": "IPv6 TCP sockets connection failures"
                  },
                  {
                    "item_name": "conn",
                    "item_type": "integer",
                    "item_optional": false,
                    "item_default": 0,
                    "item_title": "Connect",
                    "item_description": "IPv6 TCP connections established successfully"
                  },
                  {
                    "item_name": "senderr",
                    "item_type": "integer",
                    "item_optional": false,
                    "item_default": 0,
                    "item_title": "Send errors",
                    "item_description": "IPv6 TCP sockets send errors"
                  },
                  {
                    "item_name": "recverr",
                    "item_type": "integer",
                    "item_optional": false,
                    "item_default": 0,
                    "item_title": "Receive errors",
                    "item_description": "IPv6 TCP sockets receive errors"
                  }
                ]
              }
            ]
          }
        ]
      }
    ]
  }
}
