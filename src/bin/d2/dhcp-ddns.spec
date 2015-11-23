{ 
"module_spec": 
{
    "module_name": "DhcpDdns",
    "module_description": "DHPC-DDNS Service",
    "config_data": [
    { 
        "item_name": "ip-address",
        "item_type": "string",
        "item_optional": false,
        "item_default": "127.0.0.1" 
    },
    { 
        "item_name": "port",
        "item_type": "integer",
        "item_optional": true,
        "item_default": 53001 
    },
    {
        "item_name": "dns-server-timeout",
        "item_type": "integer",
        "item_optional": true,
        "item_default": 100
    },
    {
        "item_name": "ncr-protocol",
        "item_type": "string",
        "item_optional": true,
        "item_default": "UDP"
    },
    {
        "item_name": "ncr-format",
        "item_type": "string",
        "item_optional": true,
        "item_default": "JSON"
    },
    {
        "item_name": "tsig-keys",
        "item_type": "list",
        "item_optional": true, 
        "item_default": [],
        "list_item_spec":
        {
            "item_name": "tsig-key",
            "item_type": "map",
            "item_optional": false,
            "item_default": {"algorithm" : "HMAC-MD5"},
            "map_item_spec": [ 
            {
                "item_name": "name",
                "item_type": "string",
                "item_optional": false,
                "item_default": ""
            },
            {
                "item_name": "algorithm",
                "item_type": "string",
                "item_optional": false,
                "item_default": ""
            },
            {
                "item_name": "digest-bits",
                "item_type": "integer",
                "item_optional": true,
                "item_default": 0
            },
            {
                "item_name": "secret",
                "item_type": "string",
                "item_optional": false,
                "item_default": ""
            }]
        }
    },
    {
        "item_name": "forward-ddns",
        "item_type": "map",
        "item_optional": true,
         "item_default": {},
         "map_item_spec": [ 
         {
            "item_name": "ddns-domains",
            "item_type": "list",
            "item_optional": false, 
            "item_default": [],
            "list_item_spec":
            {
                "item_name": "ddns-domain",
                "item_type": "map",
                "item_optional": false,
                "item_default": {},
                "map_item_spec": [ 
                { 
                    "item_name": "name",
                    "item_type": "string",
                    "item_optional": false,
                    "item_default": ""
                },

                { 
                    "item_name": "key-name",
                    "item_type": "string",
                    "item_optional": true,
                    "item_default": "" 
                },
    
                {
                    "item_name": "dns-servers",
                    "item_type": "list",
                    "item_optional": false, 
                    "item_default": [],
                    "list_item_spec":
                    {
                        "item_name": "dns-server",
                        "item_type": "map",
                        "item_optional": false, 
                        "item_default": {},
                        "map_item_spec": [ 
                        { 
                            "item_name": "hostname",
                            "item_type": "string",
                            "item_optional": true,
                            "item_default": ""
                        },
                        { 
                            "item_name": "ip-address",
                            "item_type": "string",
                            "item_optional": true,
                            "item_default": ""
                        },
                        { 
                            "item_name": "port",
                            "item_type": "integer",
                            "item_optional": true,
                            "item_default": 53 
                        }]
                    }
                }]
            }
        }]
    },

    {
        "item_name": "reverse-ddns",
        "item_type": "map",
        "item_optional": true,
         "item_default": {},
         "map_item_spec": [ 
         { 
            "item_name": "ddns-domains",
            "item_type": "list",
            "item_optional": false, 
            "item_default": [],
            "list_item_spec":
            {
                "item_name": "ddns-domain",
                "item_type": "map",
                "item_optional": false,
                "item_default": {},
                "map_item_spec": [ 
                { 
                    "item_name": "name",
                    "item_type": "string",
                    "item_optional": false,
                    "item_default": ""
                },

                { 
                    "item_name": "key-name",
                    "item_type": "string",
                    "item_optional": true,
                    "item_default": "" 
                },
    
                {
                    "item_name": "dns-servers",
                    "item_type": "list",
                    "item_optional": false, 
                    "item_default": [],
                    "list_item_spec":
                    {
                        "item_name": "dns-server",
                        "item_type": "map",
                        "item_optional": false, 
                        "item_default": {},
                        "map_item_spec": [ 
                        { 
                            "item_name": "hostname",
                            "item_type": "string",
                            "item_optional": true,
                            "item_default": ""
                        },
                        { 
                            "item_name": "ip-address",
                            "item_type": "string",
                            "item_optional": true,
                            "item_default": ""
                        },
                        { 
                            "item_name": "port",
                            "item_type": "integer",
                            "item_optional": true,
                            "item_default": 53 
                        }]
                    }
                }]
            }
        }]
    }],

    "commands": [
        {
            "command_name": "shutdown",
            "command_description": "Shuts down kea-dhcp-ddns module server.",
            "command_args": [
            {
                "item_name": "type",
                "item_type": "string",
                "item_optional": true,
                "item_default": "normal",
                "item_description": "values: normal (default), now, or drain_first"
            }
            ]
        }
    ]
  }
}

