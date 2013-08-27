{
  "module_spec": {
    "module_name": "NotifyOutLike",
    "module_description": "Test notifier",
    "config_data": [],
    "commands": [],
    "statistics": [
      {
        "item_name": "zones",
        "item_type": "named_set",
        "item_optional": false,
        "item_default": {
          "_SERVER_" : {
            "notifyoutv4" : 0,
            "notifyoutv6" : 0
          }
        },
        "item_title": "Zone names",
        "item_description": "Zone names",
        "named_set_item_spec": {
          "item_name": "classname",
          "item_type": "named_set",
          "item_optional": false,
          "item_default": {},
          "item_title": "RR class name",
          "item_description": "RR class name",
          "named_set_item_spec": {
            "item_name": "zonename",
            "item_type": "map",
            "item_optional": false,
            "item_default": {},
            "item_title": "Zone name",
            "item_description": "Zone name",
            "map_item_spec": [
              {
                "item_name": "notifyoutv4",
                "item_type": "integer",
                "item_optional": false,
                "item_default": 0,
                "item_title": "IPv4 notifies",
                "item_description": "Number of IPv4 notifies per zone name sent out"
              },
              {
                "item_name": "notifyoutv6",
                "item_type": "integer",
                "item_optional": false,
                "item_default": 0,
                "item_title": "IPv6 notifies",
                "item_description": "Number of IPv6 notifies per zone name sent out"
              }
            ]
          }
        }
      }
    ]
  }
}
