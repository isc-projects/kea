{
  "module_spec": {
    "module_name": "Spec27",
    "commands": [
    {
        "command_name": "cmd1",
        "command_description": "command_for_unittest",
        "command_args": [ 
          {
            "item_name": "value1",
            "item_type": "integer",
            "item_optional": false,
            "item_default": 9
          },
          { "item_name": "value2",
            "item_type": "real",
            "item_optional": false,
            "item_default": 9.9
          },
          { "item_name": "value3",
            "item_type": "boolean",
            "item_optional": false,
            "item_default": false
          },
          { "item_name": "value4",
            "item_type": "string",
            "item_optional": false,
            "item_default": "default_string"
          },
          { "item_name": "value5",
            "item_type": "list",
            "item_optional": false,
            "item_default": [ "a", "b" ],
            "list_item_spec": {
              "item_name": "list_element",
              "item_type": "integer",
              "item_optional": false,
              "item_default": 8
            }
          },
          { "item_name": "value6",
            "item_type": "map",
            "item_optional": false,
            "item_default": {},
            "map_item_spec": [
              { "item_name": "v61",
                "item_type": "string",
                "item_optional": false,
                "item_default": "def"
              },
              { "item_name": "v62",
                "item_type": "boolean",
                "item_optional": false,
                "item_default": false
              }
            ]
          },
          { "item_name": "value7",
            "item_type": "list",
            "item_optional": true,
            "item_default": [ ],
            "list_item_spec": {
              "item_name": "list_element",
              "item_type": "any",
              "item_optional": true
            }
          },
          { "item_name": "value8",
            "item_type": "list",
            "item_optional": true,
            "item_default": [ ],
            "list_item_spec": {
              "item_name": "list_element",
              "item_type": "map",
              "item_optional": true,
              "item_default": { "a": "b" },
              "map_item_spec": [
                { "item_name": "a",
                  "item_type": "string",
                  "item_optional": true,
                  "item_default": "empty"
                }
              ]
            }
          },
          { "item_name": "value9",
            "item_type": "map",
            "item_optional": false,
            "item_default": {},
            "map_item_spec": [
              { "item_name": "v91",
                "item_type": "string",
                "item_optional": false,
                "item_default": "def"
              },
              { "item_name": "v92",
                "item_type": "map",
                "item_optional": false,
                "item_default": {},
                "map_item_spec": [
                  { "item_name": "v92a",
                    "item_type": "string",
                    "item_optional": false,
                    "item_default": "Hello"
                  } ,
                  {
                    "item_name": "v92b",
                    "item_type": "integer",
                    "item_optional": false,
                    "item_default": 47806
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

