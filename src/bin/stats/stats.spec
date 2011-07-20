{
  "module_spec": {
    "module_name": "Stats",
    "module_description": "Stats daemon",
    "config_data": [],
    "commands": [
      {
        "command_name": "status",
        "command_description": "identify whether stats module is alive or not",
        "command_args": []
      },
      {
        "command_name": "show",
        "command_description": "show the specified/all statistics data",
        "command_args": [
          {
            "item_name": "stats_item_name",
            "item_type": "string",
            "item_optional": true,
            "item_default": ""
          }
        ]
      },
      {
        "command_name": "set",
        "command_description": "set the value of specified name in statistics data",
        "command_args": [
          {
            "item_name": "stats_data",
            "item_type": "map",
            "item_optional": false,
            "item_default": {},
            "map_item_spec": []
          }
        ]
      },
      {
        "command_name": "remove",
        "command_description": "remove the specified name from statistics data",
        "command_args": [
          {
            "item_name": "stats_item_name",
            "item_type": "string",
            "item_optional": false,
            "item_default": ""
          }
        ]
      },
      {
        "command_name": "reset",
        "command_description": "reset all statistics data to default values except for several constant names",
        "command_args": []
      },
      {
        "command_name": "shutdown",
        "command_description": "Shut down the stats module",
        "command_args": []
      }
    ],
    "statistics": [
      {
        "item_name": "report_time",
        "item_type": "string",
        "item_optional": false,
        "item_default": "1970-01-01T00:00:00Z",
        "item_title": "Report time",
        "item_description": "A date time when stats module reports",
        "item_format": "date-time"
      },
      {
        "item_name": "boot_time",
        "item_type": "string",
        "item_optional": false,
        "item_default": "1970-01-01T00:00:00Z",
        "item_title": "Boot time",
        "item_description": "A date time when the stats module starts initially or when the stats module restarts",
        "item_format": "date-time"
      },
      {
        "item_name": "last_update_time",
        "item_type": "string",
        "item_optional": false,
        "item_default": "1970-01-01T00:00:00Z",
        "item_title": "Last update time",
        "item_description": "The latest date time when the stats module receives from other modules like auth server or boss process and so on",
        "item_format": "date-time"
      },
      {
        "item_name": "timestamp",
        "item_type": "real",
        "item_optional": false,
        "item_default": 0.0,
        "item_title": "Timestamp",
        "item_description": "A current time stamp since epoch time (1970-01-01T00:00:00Z)"
      },
      {
        "item_name": "lname",
        "item_type": "string",
        "item_optional": false,
        "item_default": "",
        "item_title": "Local Name",
        "item_description": "A localname of stats module given via CC protocol"
       }
    ]
  }
}
