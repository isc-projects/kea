{
    "module_spec": {
        "module_name": "lists",
        "module_description": "Logging options",
        "config_data": [
            {
                "item_name": "first_list_items",
                "item_type": "list",
                "item_optional": false,
                "item_default": [],
                "list_item_spec": {
                  "item_name": "first_list_item",
                  "item_type": "map",
                  "item_optional": false,
                  "item_default": {},
                  "map_item_spec": [
                  {  "item_name": "foo",
                     "item_type": "string",
                     "item_optional": false,
                     "item_default": "foo"
                  },
                  { "item_name": "second_list_items",
                    "item_type": "list",
                    "item_optional": false,
                    "item_default": [],
                    "list_item_spec": {
                      "item_name": "second_list_item",
                      "item_type": "map",
                      "item_optional": false,
                      "item_default": {},
                      "map_item_spec": [
                      { "item_name": "map_element",
                        "item_type": "map",
                        "item_optional": false,
                        "item_default": {},
                        "map_item_spec": [
                        { "item_name": "list1",
                          "item_type": "list",
                          "item_optional": false,
                          "item_default": [],
                          "list_item_spec":
                          { "item_name": "list2",
                            "item_type": "list",
                            "item_optional": false,
                            "item_default": [],
                            "list_item_spec":
                            { "item_name": "number",
                              "item_type": "integer",
                              "item_optional": false,
                              "item_default": 1
                            }
                          }
                        }]
                      }
                      ]
                    }
                  }
                  ]
                }
            }
        ]
    }
}
