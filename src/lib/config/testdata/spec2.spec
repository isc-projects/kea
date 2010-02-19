{
  "module_spec": {
    "module_name": "Spec2",
    "config_data": [
      { "item_name": "item1",
        "item_type": "integer",
        "item_optional": False,
        "item_default": 1
      },
      { "item_name": "item2",
        "item_type": "real",
        "item_optional": False,
        "item_default": 1.1
      },
      { "item_name": "item3",
        "item_type": "boolean",
        "item_optional": False,
        "item_default": True
      },
      { "item_name": "item4",
        "item_type": "string",
        "item_optional": False,
        "item_default": "test"
      },
      { "item_name": "item5",
        "item_type": "list",
        "item_optional": False,
        "item_default": [ "a", "b" ],
        "list_item_spec": {
          "item_name": "list_element",
          "item_type": "string",
          "item_optional": False,
          "item_default": ""
        }
      },
      { "item_name": "item6",
        "item_type": "map",
        "item_optional": False,
        "item_default": {},
        "map_item_spec": [
          { "item_name": "value1",
            "item_type": "string",
            "item_optional": True,
            "item_default": "default"
          },
          { "item_name": "value2",
            "item_type": "integer",
            "item_optional": True
          }
        ]
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
      },
      {
        "command_name": "shutdown",
        "command_description": "Shut down BIND 10",
        "command_args": []
      }
    ]
  }
}

