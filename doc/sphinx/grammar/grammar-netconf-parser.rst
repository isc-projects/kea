This grammar is generated from ``netconf_parser.yy``. See :ref:`netconf` for more details.

.. code-block:: BNF
   :linenos:

     Grammar

     $accept ::= start EOF

     start ::= START_JSON json

     start ::= START_NETCONF netconf_syntax_map

     start ::= START_SUB_NETCONF sub_netconf

     sub_netconf ::= "{" global_params "}"

     json ::= value

     value ::= INTEGER
          | FLOAT
          | BOOLEAN
          | STRING
          | NULL
          | map
          | list_generic

     map ::= "{" map_content "}"

     map_value ::= map

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

     netconf_syntax_map ::= "{" global_object "}"

     global_object ::= "Netconf" ":" "{" global_params "}"
                  | global_object_comma

     global_object_comma ::= global_object ","

     global_params ::= 
                  | not_empty_global_params

     not_empty_global_params ::= global_param
                            | not_empty_global_params "," global_param
                            | not_empty_global_params ","

     global_param ::= boot_update
                 | subscribe_changes
                 | validate_changes
                 | managed_servers
                 | hooks_libraries
                 | loggers
                 | user_context
                 | comment
                 | unknown_map_entry

     boot_update ::= "boot-update" ":" BOOLEAN

     subscribe_changes ::= "subscribe-changes" ":" BOOLEAN

     validate_changes ::= "validate-changes" ":" BOOLEAN

     user_context ::= "user-context" ":" map_value

     comment ::= "comment" ":" STRING

     hooks_libraries ::= "hooks-libraries" ":" "[" hooks_libraries_list "]"

     hooks_libraries_list ::= 
                         | not_empty_hooks_libraries_list

     not_empty_hooks_libraries_list ::= hooks_library
                                   | not_empty_hooks_libraries_list "," hooks_library
                                   | not_empty_hooks_libraries_list ","

     hooks_library ::= "{" hooks_params "}"

     hooks_params ::= hooks_param
                 | hooks_params "," hooks_param
                 | hooks_params ","
                 | unknown_map_entry

     hooks_param ::= library
                | parameters

     library ::= "library" ":" STRING

     parameters ::= "parameters" ":" map_value

     managed_servers ::= "managed-servers" ":" "{" servers_entries "}"

     servers_entries ::= 
                    | not_empty_servers_entries

     not_empty_servers_entries ::= server_entry
                              | not_empty_servers_entries "," server_entry
                              | not_empty_servers_entries ","

     server_entry ::= dhcp4_server
                 | dhcp6_server
                 | d2_server
                 | ca_server
                 | unknown_map_entry

     dhcp4_server ::= "dhcp4" ":" "{" managed_server_params "}"

     dhcp6_server ::= "dhcp6" ":" "{" managed_server_params "}"

     d2_server ::= "d2" ":" "{" managed_server_params "}"

     ca_server ::= "ca" ":" "{" managed_server_params "}"

     managed_server_params ::= managed_server_param
                          | managed_server_params "," managed_server_param
                          | managed_server_params ","

     managed_server_param ::= model
                         | boot_update
                         | subscribe_changes
                         | validate_changes
                         | control_socket
                         | user_context
                         | comment
                         | unknown_map_entry

     model ::= "model" ":" STRING

     control_socket ::= "control-socket" ":" "{" control_socket_params "}"

     control_socket_params ::= control_socket_param
                          | control_socket_params "," control_socket_param
                          | control_socket_params ","

     control_socket_param ::= socket_type
                         | socket_name
                         | socket_url
                         | user_context
                         | comment
                         | unknown_map_entry

     socket_type ::= "socket-type" ":" socket_type_value

     socket_type_value ::= "unix"
                      | "http"
                      | "stdout"

     socket_name ::= "socket-name" ":" STRING

     socket_url ::= "socket-url" ":" STRING

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

