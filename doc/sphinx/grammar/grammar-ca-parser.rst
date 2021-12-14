
Grammar generated on 2021-12-14 13:12. See Chapter :ref:`kea-ctrl-agent` for an explanation.

.. code-block:: BNF
   :linenos:

     Grammar

     $accept ::= start EOF

     start ::= START_JSON json

     start ::= START_AGENT agent_syntax_map

     start ::= START_SUB_AGENT sub_agent

     sub_agent ::= "{" global_params "}"

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

     list_generic ::= "[" list_content "]"

     list_content ::= 
                 | not_empty_list

     not_empty_list ::= value
                   | not_empty_list "," value

     unknown_map_entry ::= STRING ":"

     agent_syntax_map ::= "{" global_object "}"

     global_object ::= "Control-agent" ":" "{" global_params "}"

     global_params ::= global_param
                  | global_params "," global_param

     global_param ::= http_host
                 | http_port
                 | trust_anchor
                 | cert_file
                 | key_file
                 | cert_required
                 | authentication
                 | control_sockets
                 | hooks_libraries
                 | loggers
                 | user_context
                 | comment
                 | unknown_map_entry

     http_host ::= "http-host" ":" STRING

     http_port ::= "http-port" ":" INTEGER

     trust_anchor ::= "trust-anchor" ":" STRING

     cert_file ::= "cert-file" ":" STRING

     key_file ::= "key-file" ":" STRING

     cert_required ::= "cert-required" ":" BOOLEAN

     user_context ::= "user-context" ":" map_value

     comment ::= "comment" ":" STRING

     hooks_libraries ::= "hooks-libraries" ":" "[" hooks_libraries_list "]"

     hooks_libraries_list ::= 
                         | not_empty_hooks_libraries_list

     not_empty_hooks_libraries_list ::= hooks_library
                                   | not_empty_hooks_libraries_list "," hooks_library

     hooks_library ::= "{" hooks_params "}"

     hooks_params ::= hooks_param
                 | hooks_params "," hooks_param
                 | unknown_map_entry

     hooks_param ::= library
                | parameters

     library ::= "library" ":" STRING

     parameters ::= "parameters" ":" map_value

     control_sockets ::= "control-sockets" ":" "{" control_sockets_params "}"

     control_sockets_params ::= control_socket
                           | control_sockets_params "," control_socket

     control_socket ::= dhcp4_server_socket
                   | dhcp6_server_socket
                   | d2_server_socket
                   | unknown_map_entry

     dhcp4_server_socket ::= "dhcp4" ":" "{" control_socket_params "}"

     dhcp6_server_socket ::= "dhcp6" ":" "{" control_socket_params "}"

     d2_server_socket ::= "d2" ":" "{" control_socket_params "}"

     control_socket_params ::= control_socket_param
                          | control_socket_params "," control_socket_param

     control_socket_param ::= socket_name
                         | socket_type
                         | user_context
                         | comment
                         | unknown_map_entry

     socket_name ::= "socket-name" ":" STRING

     socket_type ::= "socket-type" ":" socket_type_value

     socket_type_value ::= "unix"

     authentication ::= "authentication" ":" "{" auth_params "}"

     auth_params ::= auth_param
                | auth_params "," auth_param

     auth_param ::= auth_type
               | realm
               | clients
               | comment
               | user_context
               | unknown_map_entry

     auth_type ::= "type" ":" auth_type_value

     auth_type_value ::= "basic"

     realm ::= "realm" ":" STRING

     clients ::= "clients" ":" "[" clients_list "]"

     clients_list ::= 
                 | not_empty_clients_list

     not_empty_clients_list ::= basic_auth
                           | not_empty_clients_list "," basic_auth

     basic_auth ::= "{" clients_params "}"

     clients_params ::= clients_param
                   | clients_params "," clients_param

     clients_param ::= user
                  | password
                  | user_context
                  | comment
                  | unknown_map_entry

     user ::= "user" ":" STRING

     password ::= "password" ":" STRING

     loggers ::= "loggers" ":" "[" loggers_entries "]"

     loggers_entries ::= logger_entry
                    | loggers_entries "," logger_entry

     logger_entry ::= "{" logger_params "}"

     logger_params ::= logger_param
                  | logger_params "," logger_param

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

     output_entry ::= "{" output_params_list "}"

     output_params_list ::= output_params
                       | output_params_list "," output_params

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

