{
  "module_spec": {
    "module_name": "Spec40",
    "statistics": [
      {
        "item_name": "zones",
        "item_type": "named_set",
        "item_optional": false,
        "item_default": { },
        "item_title": "Dummy name set",
        "item_description": "A dummy name set",
        "named_set_item_spec": {
          "item_name": "zonename",
          "item_type": "map",
          "item_optional": false,
          "item_default": { },
          "map_item_spec": [
            {
              "item_name": "queries.tcp",
              "item_optional": false,
              "item_type": "integer",
              "item_default": 0
            },
            {
              "item_name": "queries.udp",
              "item_optional": false,
              "item_type": "integer",
              "item_default": 0
            }
          ]
        }
      }
    ]
  }
}
