{
  "module_spec": {
    "module_name": "XfroutLike",
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
              "notifyoutv4" : 0,
              "notifyoutv6" : 0,
              "xfrrej" : 0,
              "xfrreqdone" : 0
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
                "item_name": "notifyoutv4",
                "item_type": "integer",
                "item_optional": false,
                "item_default": 0,
                "item_title": "IPv4 notifies",
                "item_description": "Number of IPv4 notifies per zone name sent out from Xfrout"
              },
              {
                "item_name": "notifyoutv6",
                "item_type": "integer",
                "item_optional": false,
                "item_default": 0,
                "item_title": "IPv6 notifies",
                "item_description": "Number of IPv6 notifies per zone name sent out from Xfrout"
              },
              {
                "item_name": "xfrrej",
                "item_type": "integer",
                "item_optional": false,
                "item_default": 0,
                "item_title": "XFR rejected requests",
                "item_description": "Number of XFR requests per zone name rejected by Xfrout"
              },
              {
                "item_name": "xfrreqdone",
                "item_type": "integer",
                "item_optional": false,
                "item_default": 0,
                "item_title": "Requested zone transfers",
                "item_description": "Number of requested zone transfers completed per zone name"
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
        "item_title": "IXFR running",
        "item_description": "Number of IXFRs in progress"
      },
      {
        "item_name": "axfr_running",
        "item_type": "integer",
        "item_optional": false,
        "item_default": 0,
        "item_title": "AXFR running",
        "item_description": "Number of AXFRs in progress"
      },
      {
        "item_name": "socket",
        "item_type": "map",
        "item_optional": false,
        "item_default": {
          "unixdomain": {
            "open": 0,
            "openfail": 0,
            "close": 0,
            "bindfail": 0,
            "acceptfail": 0,
            "accept": 0,
            "senderr": 0,
            "recverr": 0
          }
        },
        "item_title": "Socket",
        "item_description": "Socket",
        "map_item_spec": [
          {
            "item_name": "unixdomain",
            "item_type": "map",
            "item_optional": false,
            "item_default": {
              "open": 0,
              "openfail": 0,
              "close": 0,
              "bindfail": 0,
              "acceptfail": 0,
              "accept": 0,
              "senderr": 0,
              "recverr": 0
            },
            "item_title": "Unix Domain",
            "item_description": "Unix Domain",
            "map_item_spec": [
              {
                "item_name": "open",
                "item_type": "integer",
                "item_optional": false,
                "item_default": 0,
                "item_title": "Open",
                "item_description": "Unix Domain sockets opened successfully"
              },
              {
                "item_name": "openfail",
                "item_type": "integer",
                "item_optional": false,
                "item_default": 0,
                "item_title": "Open failures",
                "item_description": "Unix Domain sockets open failures"
              },
              {
                "item_name": "close",
                "item_type": "integer",
                "item_optional": false,
                "item_default": 0,
                "item_title": "Close",
                "item_description": "Unix Domain sockets closed"
              },
              {
                "item_name": "bindfail",
                "item_type": "integer",
                "item_optional": false,
                "item_default": 0,
                "item_title": "Bind failures",
                "item_description": "Unix Domain sockets bind failures"
              },
              {
                "item_name": "acceptfail",
                "item_type": "integer",
                "item_optional": false,
                "item_default": 0,
                "item_title": "Accept failures",
                "item_description": "Unix Domain sockets incoming accept failures"
              },
              {
                "item_name": "accept",
                "item_type": "integer",
                "item_optional": false,
                "item_default": 0,
                "item_title": "Accept",
                "item_description": "Unix Domain sockets incoming connections successfully accepted"
              },
              {
                "item_name": "senderr",
                "item_type": "integer",
                "item_optional": false,
                "item_default": 0,
                "item_title": "Send errors",
                "item_description": "Unix Domain sockets send errors"
              },
              {
                "item_name": "recverr",
                "item_type": "integer",
                "item_optional": false,
                "item_default": 0,
                "item_title": "Receive errors",
                "item_description": "Unix Domain sockets receive errors"
              }
            ]
          }
        ]
      }
    ]
  }
}

