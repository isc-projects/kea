This grammar is generated from ``d2_parser.yy``. See :ref:`dhcp-ddns-server` for more details.

.. code-block:: BNF
   :linenos:

     Grammar

     $accept ::= start EOF

     start ::= TOPLEVEL_JSON sub_json

     start ::= TOPLEVEL_DHCPDDNS syntax_map

     start ::= SUB_DHCPDDNS sub_dhcpddns

     start ::= SUB_TSIG_KEY sub_tsig_key

     start ::= SUB_TSIG_KEYS sub_tsig_keys

     start ::= SUB_DDNS_DOMAIN sub_ddns_domain

     start ::= SUB_DDNS_DOMAINS sub_ddns_domains

     start ::= SUB_DNS_SERVER sub_dns_server

     start ::= SUB_DNS_SERVERS sub_dns_servers

     start ::= SUB_HOOKS_LIBRARY sub_hooks_library

     value ::= INTEGER
          | FLOAT
          | BOOLEAN
          | STRING
          | NULL
          | map2
          | list_generic

     sub_json ::= value

     map2 ::= "{" map_content "}"

     map_value ::= map2

     map_content ::= 
                | not_empty_map

     not_empty_map ::= STRING ":" value
                  | not_empty_map "," STRING ":" value
                  | not_empty_map ","

     list_generic ::= "[" list_content "]"

     list_content ::= 
                 | not_empty_list

     not_empty_list ::= value
                   | not_empty_list "," value
                   | not_empty_list ","

     unknown_map_entry ::= STRING ":"

     syntax_map ::= "{" global_object "}"

     global_object ::= "DhcpDdns" ":" "{" dhcpddns_params "}"
                  | global_object_comma

     global_object_comma ::= global_object ","

     sub_dhcpddns ::= "{" dhcpddns_params "}"

     dhcpddns_params ::= dhcpddns_param
                    | dhcpddns_params "," dhcpddns_param
                    | dhcpddns_params ","

     dhcpddns_param ::= ip_address
                   | port
                   | dns_server_timeout
                   | ncr_protocol
                   | ncr_format
                   | forward_ddns
                   | reverse_ddns
                   | tsig_keys
                   | control_socket
                   | hooks_libraries
                   | loggers
                   | user_context
                   | comment
                   | unknown_map_entry

     ip_address ::= "ip-address" ":" STRING

     port ::= "port" ":" INTEGER

     dns_server_timeout ::= "dns-server-timeout" ":" INTEGER

     ncr_protocol ::= "ncr-protocol" ":" ncr_protocol_value

     ncr_protocol_value ::= "UDP"
                       | "TCP"

     ncr_format ::= "ncr-format" ":" "JSON"

     user_context ::= "user-context" ":" map_value

     comment ::= "comment" ":" STRING

     forward_ddns ::= "forward-ddns" ":" "{" ddns_mgr_params "}"

     reverse_ddns ::= "reverse-ddns" ":" "{" ddns_mgr_params "}"

     ddns_mgr_params ::= 
                    | not_empty_ddns_mgr_params

     not_empty_ddns_mgr_params ::= ddns_mgr_param
                              | ddns_mgr_params "," ddns_mgr_param
                              | ddns_mgr_params ","

     ddns_mgr_param ::= ddns_domains
                   | unknown_map_entry

     ddns_domains ::= "ddns-domains" ":" "[" ddns_domain_list "]"

     sub_ddns_domains ::= "[" ddns_domain_list "]"

     ddns_domain_list ::= 
                     | not_empty_ddns_domain_list

     not_empty_ddns_domain_list ::= ddns_domain
                               | not_empty_ddns_domain_list "," ddns_domain
                               | not_empty_ddns_domain_list ","

     ddns_domain ::= "{" ddns_domain_params "}"

     sub_ddns_domain ::= "{" ddns_domain_params "}"

     ddns_domain_params ::= ddns_domain_param
                       | ddns_domain_params "," ddns_domain_param
                       | ddns_domain_params ","

     ddns_domain_param ::= ddns_domain_name
                      | ddns_key_name
                      | dns_servers
                      | user_context
                      | comment
                      | unknown_map_entry

     ddns_domain_name ::= "name" ":" STRING

     ddns_key_name ::= "key-name" ":" STRING

     dns_servers ::= "dns-servers" ":" "[" dns_server_list "]"

     sub_dns_servers ::= "[" dns_server_list "]"

     dns_server_list ::= dns_server
                    | dns_server_list "," dns_server
                    | dns_server_list ","

     dns_server ::= "{" dns_server_params "}"

     sub_dns_server ::= "{" dns_server_params "}"

     dns_server_params ::= dns_server_param
                      | dns_server_params "," dns_server_param
                      | dns_server_params ","

     dns_server_param ::= dns_server_hostname
                     | dns_server_ip_address
                     | dns_server_port
                     | ddns_key_name
                     | user_context
                     | comment
                     | unknown_map_entry

     dns_server_hostname ::= "hostname" ":" STRING

     dns_server_ip_address ::= "ip-address" ":" STRING

     dns_server_port ::= "port" ":" INTEGER

     tsig_keys ::= "tsig-keys" ":" "[" tsig_keys_list "]"

     sub_tsig_keys ::= "[" tsig_keys_list "]"

     tsig_keys_list ::= 
                   | not_empty_tsig_keys_list

     not_empty_tsig_keys_list ::= tsig_key
                             | not_empty_tsig_keys_list "," tsig_key
                             | not_empty_tsig_keys_list ","

     tsig_key ::= "{" tsig_key_params "}"

     sub_tsig_key ::= "{" tsig_key_params "}"

     tsig_key_params ::= tsig_key_param
                    | tsig_key_params "," tsig_key_param
                    | tsig_key_params ","

     tsig_key_param ::= tsig_key_name
                   | tsig_key_algorithm
                   | tsig_key_digest_bits
                   | tsig_key_secret
                   | user_context
                   | comment
                   | unknown_map_entry

     tsig_key_name ::= "name" ":" STRING

     tsig_key_algorithm ::= "algorithm" ":" STRING

     tsig_key_digest_bits ::= "digest-bits" ":" INTEGER

     tsig_key_secret ::= "secret" ":" STRING

     control_socket ::= "control-socket" ":" "{" control_socket_params "}"

     control_socket_params ::= control_socket_param
                          | control_socket_params "," control_socket_param
                          | control_socket_params ","

     control_socket_param ::= control_socket_type
                         | control_socket_name
                         | user_context
                         | comment
                         | unknown_map_entry

     control_socket_type ::= "socket-type" ":" STRING

     control_socket_name ::= "socket-name" ":" STRING

     hooks_libraries ::= "hooks-libraries" ":" "[" hooks_libraries_list "]"

     hooks_libraries_list ::= 
                         | not_empty_hooks_libraries_list

     not_empty_hooks_libraries_list ::= hooks_library
                                   | not_empty_hooks_libraries_list "," hooks_library
                                   | not_empty_hooks_libraries_list ","

     hooks_library ::= "{" hooks_params "}"

     sub_hooks_library ::= "{" hooks_params "}"

     hooks_params ::= hooks_param
                 | hooks_params "," hooks_param
                 | hooks_params ","
                 | unknown_map_entry

     hooks_param ::= library
                | parameters

     library ::= "library" ":" STRING

     parameters ::= "parameters" ":" map_value

     loggers ::= "loggers" ":" "[" loggers_entries "]"

     loggers_entries ::= logger_entry
                    | loggers_entries "," logger_entry
                    | loggers_entries ","

     logger_entry ::= "{" logger_params "}"

     logger_params ::= logger_param
                  | logger_params "," logger_param
                  | logger_params ","

     logger_param ::= name
                 | output_options_list
                 | debuglevel
                 | severity
                 | user_context
                 | comment
                 | unknown_map_entry

     name ::= "name" ":" STRING

     debuglevel ::= "debuglevel" ":" INTEGER

     severity ::= "severity" ":" STRING

     output_options_list ::= "output_options" ":" "[" output_options_list_content "]"

     output_options_list_content ::= output_entry
                                | output_options_list_content "," output_entry
                                | output_options_list_content ","

     output_entry ::= "{" output_params_list "}"

     output_params_list ::= output_params
                       | output_params_list "," output_params
                       | output_params_list ","

     output_params ::= output
                  | flush
                  | maxsize
                  | maxver
                  | pattern

     output ::= "output" ":" STRING

     flush ::= "flush" ":" BOOLEAN

     maxsize ::= "maxsize" ":" INTEGER

     maxver ::= "maxver" ":" INTEGER

     pattern ::= "pattern" ":" STRING

