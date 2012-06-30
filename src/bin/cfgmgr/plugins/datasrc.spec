{
    "module_spec": {
        "module_name": "data_sources",
        "module_description": "The sources of authoritative DNS data",
        "config_data": [
            {
                "item_name": "classes",
                "item_type": "named_set",
                "item_optional": false,
                "item_default": {},
                "named_set_item_spec": {
                    "item_name": "class",
                    "item_type": "list",
                    "item_optional": false,
                    "item_default": [],
                    "list_item_spec": {
                        "item_name": "source",
                        "item_type": "map",
                        "item_optional": false,
                        "item_default": {},
                        "map_item_spec": [
                            {
                                "item_name": "type",
                                "item_type": "string",
                                "item_optional": false,
                                "item_default": ""
                            },
                            {
                                "item_name": "params",
                                "item_type": "any",
                                "item_optional": false,
                                "item_default": null
                            },
                            {
                                "item_name": "cache-enable",
                                "item_type": "boolean",
                                "item_optional": false,
                                "item_default": false
                            },
                            {
                                "item_name": "cache-zones",
                                "item_type": "list",
                                "item_optional": true,
                                "list_item_spec": {
                                    "item_name": "zone",
                                    "item_type": "string",
                                    "item_optional": false,
                                    "item_default": ""
                                }
                            }
                        ]
                    }
                }
            }
        ],
        "commands": []
    }
}
