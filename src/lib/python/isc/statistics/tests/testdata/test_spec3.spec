{
  "module_spec": {
    "module_name": "XfrinLike",
    "module_description": "XFR in daemon",
    "config_data": [],
    "commands": [],
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
        "item_description": "Zone names for Xfrout statistics",
        "named_set_item_spec": {
          "item_name": "classname",
          "item_type": "named_set",
          "item_optional": false,
          "item_default": {},
          "item_title": "RR class name",
          "item_description": "RR class name for Xfrout statistics",
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
                "item_name": "last_ixfr_duration",
                "item_type": "real",
                "item_optional": false,
                "item_default": 0.0,
                "item_title": "Last IXFR duration",
                "item_description": "Duration of the last IXFR. 0.0 means no successful IXFR done."
              },
              {
                "item_name": "last_axfr_duration",
                "item_type": "real",
                "item_optional": false,
                "item_default": 0.0,
                "item_title": "Last AXFR duration",
                "item_description": "Duration of the last AXFR. 0.0 means no successful AXFR done."
              }
            ]
          }
        }
      },
      {
        "item_name": "ixfr_running",
        "item_type": "integer",
        "item_optional": false,
        "item_default": 0,
        "item_title": "IXFRs running",
        "item_description": "Number of IXFRs in progress"
      },
      {
        "item_name": "axfr_running",
        "item_type": "integer",
        "item_optional": false,
        "item_default": 0,
        "item_title": "AXFRs running",
        "item_description": "Number of AXFRs in progress"
      },
      {
        "item_name": "ixfr_deferred",
        "item_type": "integer",
        "item_optional": false,
        "item_default": 0,
        "item_title": "IXFRs deferred",
        "item_description": "Number of deferred IXFRs"
      },
      {
        "item_name": "axfr_deferred",
        "item_type": "integer",
        "item_optional": false,
        "item_default": 0,
        "item_title": "AXFRs deferred",
        "item_description": "Number of deferred AXFRs"
      },
      {
        "item_name": "soa_in_progress",
        "item_type": "integer",
        "item_optional": false,
        "item_default": 0,
        "item_title": "SOA queries",
        "item_description": "Number of SOA queries in progress"
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
        "item_description": "Socket",
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
            "item_description": "IPv4",
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
                "item_description": "TCP/IP",
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
            "item_description": "IPv6",
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
                "item_description": "TCP/IP",
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
