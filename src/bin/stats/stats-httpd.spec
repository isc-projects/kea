{
  "module_spec": {
    "module_name": "StatsHttpd",
    "module_description": "Stats HTTP daemon",
    "config_data": [
      {
        "item_name": "listen_on",
        "item_type": "list",
        "item_optional": false,
        "item_default": [
          {
            "address": "127.0.0.1",
            "port": 8000
          }
        ],
        "list_item_spec": {
          "item_name": "address",
          "item_type": "map",
          "item_optional": false,
          "item_default": {},
          "map_item_spec": [
            {
              "item_name": "address",
              "item_type": "string",
              "item_optional": true,
              "item_default": "127.0.0.1",
              "item_description": "listen-on address for HTTP"
            },
            {
              "item_name": "port",
              "item_type": "integer",
              "item_optional": true,
              "item_default": 8000,
              "item_description": "listen-on port for HTTP"
            }
          ]
        },
        "item_description": "http listen-on address and port"
      }
    ],
    "commands": [
      {
        "command_name": "status",
        "command_description": "Status of the stats httpd",
        "command_args": []
      },
      {
        "command_name": "shutdown",
        "command_description": "Shut down the stats httpd",
        "command_args": [
          {
            "item_name": "pid",
            "item_type": "integer",
            "item_optional": true
          }
        ]
      }
    ]
  }
}
