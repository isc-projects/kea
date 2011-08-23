{
  "module_spec": {
    "module_name": "Stats",
    "module_description": "Statistics data schema",
    "config_data": [
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
        "item_name": "bind10.boot_time",
        "item_type": "string",
        "item_optional": false,
        "item_default": "1970-01-01T00:00:00Z",
        "item_title": "bind10.BootTime",
        "item_description": "A date time when bind10 process starts initially",
        "item_format": "date-time"
      },
      {
        "item_name": "stats.boot_time",
        "item_type": "string",
        "item_optional": false,
        "item_default": "1970-01-01T00:00:00Z",
        "item_title": "stats.BootTime",
        "item_description": "A date time when the stats module starts initially or when the stats module restarts",
        "item_format": "date-time"
      },
      {
        "item_name": "stats.start_time",
        "item_type": "string",
        "item_optional": false,
        "item_default": "1970-01-01T00:00:00Z",
        "item_title": "stats.StartTime",
        "item_description": "A date time when the stats module starts collecting data or resetting values last time",
        "item_format": "date-time"
      },
      {
        "item_name": "stats.last_update_time",
        "item_type": "string",
        "item_optional": false,
        "item_default": "1970-01-01T00:00:00Z",
        "item_title": "stats.LastUpdateTime",
        "item_description": "The latest date time when the stats module receives from other modules like auth server or boss process and so on",
        "item_format": "date-time"
      },
      {
        "item_name": "stats.timestamp",
        "item_type": "real",
        "item_optional": false,
        "item_default": 0.0,
        "item_title": "stats.Timestamp",
        "item_description": "A current time stamp since epoch time (1970-01-01T00:00:00Z)"
      },
      {
        "item_name": "stats.lname",
        "item_type": "string",
        "item_optional": false,
        "item_default": "",
        "item_title": "stats.LocalName",
        "item_description": "A localname of stats module given via CC protocol"
      },
      {
        "item_name": "auth.queries.tcp",
        "item_type": "integer",
        "item_optional": false,
        "item_default": 0,
        "item_title": "auth.queries.tcp",
        "item_description": "A number of total query counts which all auth servers receive over TCP since they started initially"
      },
      {
        "item_name": "auth.queries.udp",
        "item_type": "integer",
        "item_optional": false,
        "item_default": 0,
        "item_title": "auth.queries.udp",
        "item_description": "A number of total query counts which all auth servers receive over UDP since they started initially"
      }
    ],
    "commands": []
  }
}
