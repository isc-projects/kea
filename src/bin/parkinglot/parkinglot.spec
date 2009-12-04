{
  "data_specification": {
    "module_name": "ParkingLot",
    "config_data": [
      {
        "item_name": "port",
        "item_type": "integer",
        "item_optional": false,
        "item_default": 5300
      },
      {
        "item_name": "zones",
        "item_type": "list",
        "item_optional": false,
        "item_default": [ ],
        "list_item_spec": {
          "item_name": "zone_name",
          "item_type": "string",
          "item_optional": false,
          "item_default": ""
        }
      }
    ],
    "commands": [
      {
        "command_name": "print_message",
        "command_description": "Print the given message to stdout",
        "command_args": [ {
          "item_name": "message",
          "item_type": "string",
          "item_optional": False,
          "item_default": ""
        } ]
      }
    ]
  }
}

