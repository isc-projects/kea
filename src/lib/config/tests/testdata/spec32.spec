{
  "module_spec": {
    "module_name": "Spec32",
    "config_data": [
      { "item_name": "named_set_item",
        "item_type": "named_set",
        "item_optional": false,
        "item_default": { "a": 1, "b": 2 },
        "named_set_item_spec": {
          "item_name": "named_set_element",
          "item_type": "integer",
          "item_optional": false,
          "item_default": 3
        }
      },
      { "item_name": "named_set_item2",
        "item_type": "named_set",
        "item_optional": true,
        "item_default": { },
        "named_set_item_spec": {
          "item_name": "named_set_element",
          "item_type": "map",
          "item_optional": false,
          "item_default": {},
          "map_item_spec": [
          { "item_name": "first",
            "item_type": "integer",
            "item_optional": true
          },
          { "item_name": "second",
            "item_type": "string",
            "item_optional": true
          }
          ]
        }
      },
      { "item_name": "named_set_item3",
        "item_type": "named_set",
        "item_optional": true,
        "item_default": { "values": [ 1, 2, 3 ] },
        "named_set_item_spec": {
          "item_name": "named_set_element",
          "item_type": "list",
          "item_optional": false,
          "item_default": [],
          "list_item_spec":
          { "item_name": "list_value",
            "item_type": "integer",
            "item_optional": true
          }
        }
      },
      { "item_name": "named_set_item4",
        "item_type": "named_set",
        "item_optional": true,
        "item_default": {},
        "named_set_item_spec": {
          "item_name": "named_set_element",
          "item_type": "named_set",
          "item_optional": false,
          "item_default": { "a": 1, "b": 2 },
          "named_set_item_spec":
          { "item_name": "named_set_element",
            "item_type": "integer",
            "item_optional": true
          }
        }
      }
    ]
  }
}

