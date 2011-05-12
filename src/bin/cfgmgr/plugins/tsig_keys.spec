{
    "module_spec": {
        "module_name": "tsig_keys",
        "module_description": "The TSIG keyring is stored here",
        "config_data": [
            {
                "item_name": "keys",
                "item_type": "list",
                "item_optional": false,
                "item_default": [],
                "list_item_spec": {
                    "item_name": "key",
                    "item_type": "string",
                    "item_optional": false,
                    "item_default": ""
                }
            }
        ],
        "commands": []
    }
}
