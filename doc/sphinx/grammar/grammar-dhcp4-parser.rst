This grammar is generated from ``dhcp4_parser.yy``. See :ref:`dhcp4` for more details.

.. code-block:: BNF
   :linenos:

     Grammar

     $accept ::= start EOF

     start ::= TOPLEVEL_JSON sub_json

     start ::= TOPLEVEL_DHCP4 syntax_map

     start ::= SUB_DHCP4 sub_dhcp4

     start ::= SUB_INTERFACES4 sub_interfaces4

     start ::= SUB_SUBNET4 sub_subnet4

     start ::= SUB_POOL4 sub_pool4

     start ::= SUB_RESERVATION sub_reservation

     start ::= SUB_OPTION_DEFS sub_option_def_list

     start ::= SUB_OPTION_DEF sub_option_def

     start ::= SUB_OPTION_DATA sub_option_data

     start ::= SUB_HOOKS_LIBRARY sub_hooks_library

     start ::= SUB_DHCP_DDNS sub_dhcp_ddns

     start ::= SUB_CONFIG_CONTROL sub_config_control

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

     list_strings ::= "[" list_strings_content "]"

     list_strings_content ::= 
                         | not_empty_list_strings

     not_empty_list_strings ::= STRING
                           | not_empty_list_strings "," STRING
                           | not_empty_list_strings ","

     unknown_map_entry ::= STRING ":"

     syntax_map ::= "{" global_object "}"

     global_object ::= "Dhcp4" ":" "{" global_params "}"
                  | global_object_comma

     global_object_comma ::= global_object ","

     sub_dhcp4 ::= "{" global_params "}"

     global_params ::= global_param
                  | global_params "," global_param
                  | global_params ","

     global_param ::= valid_lifetime
                 | min_valid_lifetime
                 | max_valid_lifetime
                 | renew_timer
                 | rebind_timer
                 | decline_probation_period
                 | subnet4_list
                 | shared_networks
                 | interfaces_config
                 | lease_database
                 | hosts_database
                 | hosts_databases
                 | host_reservation_identifiers
                 | client_classes
                 | option_def_list
                 | option_data_list
                 | hooks_libraries
                 | expired_leases_processing
                 | dhcp4o6_port
                 | control_socket
                 | dhcp_queue_control
                 | dhcp_ddns
                 | echo_client_id
                 | match_client_id
                 | authoritative
                 | next_server
                 | server_hostname
                 | boot_file_name
                 | user_context
                 | comment
                 | sanity_checks
                 | reservations
                 | config_control
                 | server_tag
                 | reservation_mode
                 | reservations_global
                 | reservations_in_subnet
                 | reservations_out_of_pool
                 | calculate_tee_times
                 | t1_percent
                 | t2_percent
                 | cache_threshold
                 | cache_max_age
                 | loggers
                 | hostname_char_set
                 | hostname_char_replacement
                 | ddns_send_updates
                 | ddns_override_no_update
                 | ddns_override_client_update
                 | ddns_replace_client_name
                 | ddns_generated_prefix
                 | ddns_qualifying_suffix
                 | ddns_update_on_renew
                 | ddns_use_conflict_resolution
                 | store_extended_info
                 | statistic_default_sample_count
                 | statistic_default_sample_age
                 | dhcp_multi_threading
                 | ip_reservations_unique
                 | reservations_lookup_first
                 | compatibility
                 | parked_packet_limit
                 | unknown_map_entry

     valid_lifetime ::= "valid-lifetime" ":" INTEGER

     min_valid_lifetime ::= "min-valid-lifetime" ":" INTEGER

     max_valid_lifetime ::= "max-valid-lifetime" ":" INTEGER

     renew_timer ::= "renew-timer" ":" INTEGER

     rebind_timer ::= "rebind-timer" ":" INTEGER

     calculate_tee_times ::= "calculate-tee-times" ":" BOOLEAN

     t1_percent ::= "t1-percent" ":" FLOAT

     t2_percent ::= "t2-percent" ":" FLOAT

     cache_threshold ::= "cache-threshold" ":" FLOAT

     cache_max_age ::= "cache-max-age" ":" INTEGER

     decline_probation_period ::= "decline-probation-period" ":" INTEGER

     server_tag ::= "server-tag" ":" STRING

     parked_packet_limit ::= "parked-packet-limit" ":" INTEGER

     echo_client_id ::= "echo-client-id" ":" BOOLEAN

     match_client_id ::= "match-client-id" ":" BOOLEAN

     authoritative ::= "authoritative" ":" BOOLEAN

     ddns_send_updates ::= "ddns-send-updates" ":" BOOLEAN

     ddns_override_no_update ::= "ddns-override-no-update" ":" BOOLEAN

     ddns_override_client_update ::= "ddns-override-client-update" ":" BOOLEAN

     ddns_replace_client_name ::= "ddns-replace-client-name" ":" ddns_replace_client_name_value

     ddns_replace_client_name_value ::= "when-present"
                                   | "never"
                                   | "always"
                                   | "when-not-present"
                                   | BOOLEAN

     ddns_generated_prefix ::= "ddns-generated-prefix" ":" STRING

     ddns_qualifying_suffix ::= "ddns-qualifying-suffix" ":" STRING

     ddns_update_on_renew ::= "ddns-update-on-renew" ":" BOOLEAN

     ddns_use_conflict_resolution ::= "ddns-use-conflict-resolution" ":" BOOLEAN

     hostname_char_set ::= "hostname-char-set" ":" STRING

     hostname_char_replacement ::= "hostname-char-replacement" ":" STRING

     store_extended_info ::= "store-extended-info" ":" BOOLEAN

     statistic_default_sample_count ::= "statistic-default-sample-count" ":" INTEGER

     statistic_default_sample_age ::= "statistic-default-sample-age" ":" INTEGER

     ip_reservations_unique ::= "ip-reservations-unique" ":" BOOLEAN

     reservations_lookup_first ::= "reservations-lookup-first" ":" BOOLEAN

     interfaces_config ::= "interfaces-config" ":" "{" interfaces_config_params "}"

     interfaces_config_params ::= interfaces_config_param
                             | interfaces_config_params "," interfaces_config_param
                             | interfaces_config_params ","

     interfaces_config_param ::= interfaces_list
                            | dhcp_socket_type
                            | outbound_interface
                            | re_detect
                            | user_context
                            | comment
                            | unknown_map_entry

     sub_interfaces4 ::= "{" interfaces_config_params "}"

     interfaces_list ::= "interfaces" ":" list_strings

     dhcp_socket_type ::= "dhcp-socket-type" ":" socket_type

     socket_type ::= "raw"
                | "udp"

     outbound_interface ::= "outbound-interface" ":" outbound_interface_value

     outbound_interface_value ::= "same-as-inbound"
                             | "use-routing"

     re_detect ::= "re-detect" ":" BOOLEAN

     lease_database ::= "lease-database" ":" "{" database_map_params "}"

     sanity_checks ::= "sanity-checks" ":" "{" sanity_checks_params "}"

     sanity_checks_params ::= sanity_checks_param
                         | sanity_checks_params "," sanity_checks_param
                         | sanity_checks_params ","

     sanity_checks_param ::= lease_checks

     lease_checks ::= "lease-checks" ":" STRING

     hosts_database ::= "hosts-database" ":" "{" database_map_params "}"

     hosts_databases ::= "hosts-databases" ":" "[" database_list "]"

     database_list ::= 
                  | not_empty_database_list

     not_empty_database_list ::= database
                            | not_empty_database_list "," database
                            | not_empty_database_list ","

     database ::= "{" database_map_params "}"

     database_map_params ::= database_map_param
                        | database_map_params "," database_map_param
                        | database_map_params ","

     database_map_param ::= database_type
                       | user
                       | password
                       | host
                       | port
                       | name
                       | persist
                       | lfc_interval
                       | readonly
                       | connect_timeout
                       | contact_points
                       | max_reconnect_tries
                       | reconnect_wait_time
                       | on_fail
                       | request_timeout
                       | tcp_keepalive
                       | tcp_nodelay
                       | keyspace
                       | consistency
                       | serial_consistency
                       | max_row_errors
                       | trust_anchor
                       | cert_file
                       | key_file
                       | cipher_list
                       | unknown_map_entry

     database_type ::= "type" ":" db_type

     db_type ::= "memfile"
            | "mysql"
            | "postgresql"
            | "cql"

     user ::= "user" ":" STRING

     password ::= "password" ":" STRING

     host ::= "host" ":" STRING

     port ::= "port" ":" INTEGER

     name ::= "name" ":" STRING

     persist ::= "persist" ":" BOOLEAN

     lfc_interval ::= "lfc-interval" ":" INTEGER

     readonly ::= "readonly" ":" BOOLEAN

     connect_timeout ::= "connect-timeout" ":" INTEGER

     request_timeout ::= "request-timeout" ":" INTEGER

     tcp_keepalive ::= "tcp-keepalive" ":" INTEGER

     tcp_nodelay ::= "tcp-nodelay" ":" BOOLEAN

     contact_points ::= "contact-points" ":" STRING

     keyspace ::= "keyspace" ":" STRING

     consistency ::= "consistency" ":" STRING

     serial_consistency ::= "serial-consistency" ":" STRING

     max_reconnect_tries ::= "max-reconnect-tries" ":" INTEGER

     reconnect_wait_time ::= "reconnect-wait-time" ":" INTEGER

     on_fail ::= "on-fail" ":" on_fail_mode

     on_fail_mode ::= "stop-retry-exit"
                 | "serve-retry-exit"
                 | "serve-retry-continue"

     max_row_errors ::= "max-row-errors" ":" INTEGER

     trust_anchor ::= "trust-anchor" ":" STRING

     cert_file ::= "cert-file" ":" STRING

     key_file ::= "key-file" ":" STRING

     cipher_list ::= "cipher-list" ":" STRING

     host_reservation_identifiers ::= "host-reservation-identifiers" ":" "[" host_reservation_identifiers_list "]"

     host_reservation_identifiers_list ::= host_reservation_identifier
                                      | host_reservation_identifiers_list "," host_reservation_identifier
                                      | host_reservation_identifiers_list ","

     host_reservation_identifier ::= duid_id
                                | hw_address_id
                                | circuit_id
                                | client_id
                                | flex_id

     duid_id ::= "duid"

     hw_address_id ::= "hw-address"

     circuit_id ::= "circuit-id"

     client_id ::= "client-id"

     flex_id ::= "flex-id"

     dhcp_multi_threading ::= "multi-threading" ":" "{" multi_threading_params "}"

     multi_threading_params ::= multi_threading_param
                           | multi_threading_params "," multi_threading_param
                           | multi_threading_params ","

     multi_threading_param ::= enable_multi_threading
                          | thread_pool_size
                          | packet_queue_size
                          | user_context
                          | comment
                          | unknown_map_entry

     enable_multi_threading ::= "enable-multi-threading" ":" BOOLEAN

     thread_pool_size ::= "thread-pool-size" ":" INTEGER

     packet_queue_size ::= "packet-queue-size" ":" INTEGER

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

     expired_leases_processing ::= "expired-leases-processing" ":" "{" expired_leases_params "}"

     expired_leases_params ::= expired_leases_param
                          | expired_leases_params "," expired_leases_param
                          | expired_leases_params ","

     expired_leases_param ::= reclaim_timer_wait_time
                         | flush_reclaimed_timer_wait_time
                         | hold_reclaimed_time
                         | max_reclaim_leases
                         | max_reclaim_time
                         | unwarned_reclaim_cycles

     reclaim_timer_wait_time ::= "reclaim-timer-wait-time" ":" INTEGER

     flush_reclaimed_timer_wait_time ::= "flush-reclaimed-timer-wait-time" ":" INTEGER

     hold_reclaimed_time ::= "hold-reclaimed-time" ":" INTEGER

     max_reclaim_leases ::= "max-reclaim-leases" ":" INTEGER

     max_reclaim_time ::= "max-reclaim-time" ":" INTEGER

     unwarned_reclaim_cycles ::= "unwarned-reclaim-cycles" ":" INTEGER

     subnet4_list ::= "subnet4" ":" "[" subnet4_list_content "]"

     subnet4_list_content ::= 
                         | not_empty_subnet4_list

     not_empty_subnet4_list ::= subnet4
                           | not_empty_subnet4_list "," subnet4
                           | not_empty_subnet4_list ","

     subnet4 ::= "{" subnet4_params "}"

     sub_subnet4 ::= "{" subnet4_params "}"

     subnet4_params ::= subnet4_param
                   | subnet4_params "," subnet4_param
                   | subnet4_params ","

     subnet4_param ::= valid_lifetime
                  | min_valid_lifetime
                  | max_valid_lifetime
                  | renew_timer
                  | rebind_timer
                  | option_data_list
                  | pools_list
                  | subnet
                  | interface
                  | id
                  | client_class
                  | require_client_classes
                  | reservations
                  | reservation_mode
                  | reservations_global
                  | reservations_in_subnet
                  | reservations_out_of_pool
                  | relay
                  | match_client_id
                  | authoritative
                  | next_server
                  | server_hostname
                  | boot_file_name
                  | subnet_4o6_interface
                  | subnet_4o6_interface_id
                  | subnet_4o6_subnet
                  | user_context
                  | comment
                  | calculate_tee_times
                  | t1_percent
                  | t2_percent
                  | cache_threshold
                  | cache_max_age
                  | ddns_send_updates
                  | ddns_override_no_update
                  | ddns_override_client_update
                  | ddns_replace_client_name
                  | ddns_generated_prefix
                  | ddns_qualifying_suffix
                  | ddns_update_on_renew
                  | ddns_use_conflict_resolution
                  | hostname_char_set
                  | hostname_char_replacement
                  | store_extended_info
                  | unknown_map_entry

     subnet ::= "subnet" ":" STRING

     subnet_4o6_interface ::= "4o6-interface" ":" STRING

     subnet_4o6_interface_id ::= "4o6-interface-id" ":" STRING

     subnet_4o6_subnet ::= "4o6-subnet" ":" STRING

     interface ::= "interface" ":" STRING

     client_class ::= "client-class" ":" STRING

     require_client_classes ::= "require-client-classes" ":" list_strings

     reservations_global ::= "reservations-global" ":" BOOLEAN

     reservations_in_subnet ::= "reservations-in-subnet" ":" BOOLEAN

     reservations_out_of_pool ::= "reservations-out-of-pool" ":" BOOLEAN

     reservation_mode ::= "reservation-mode" ":" hr_mode

     hr_mode ::= "disabled"
            | "out-of-pool"
            | "global"
            | "all"

     id ::= "id" ":" INTEGER

     shared_networks ::= "shared-networks" ":" "[" shared_networks_content "]"

     shared_networks_content ::= 
                            | shared_networks_list

     shared_networks_list ::= shared_network
                         | shared_networks_list "," shared_network
                         | shared_networks_list ","

     shared_network ::= "{" shared_network_params "}"

     shared_network_params ::= shared_network_param
                          | shared_network_params "," shared_network_param
                          | shared_network_params ","

     shared_network_param ::= name
                         | subnet4_list
                         | interface
                         | renew_timer
                         | rebind_timer
                         | option_data_list
                         | match_client_id
                         | authoritative
                         | next_server
                         | server_hostname
                         | boot_file_name
                         | relay
                         | reservation_mode
                         | reservations_global
                         | reservations_in_subnet
                         | reservations_out_of_pool
                         | client_class
                         | require_client_classes
                         | valid_lifetime
                         | min_valid_lifetime
                         | max_valid_lifetime
                         | user_context
                         | comment
                         | calculate_tee_times
                         | t1_percent
                         | t2_percent
                         | cache_threshold
                         | cache_max_age
                         | ddns_send_updates
                         | ddns_override_no_update
                         | ddns_override_client_update
                         | ddns_replace_client_name
                         | ddns_generated_prefix
                         | ddns_qualifying_suffix
                         | ddns_update_on_renew
                         | ddns_use_conflict_resolution
                         | hostname_char_set
                         | hostname_char_replacement
                         | store_extended_info
                         | unknown_map_entry

     option_def_list ::= "option-def" ":" "[" option_def_list_content "]"

     sub_option_def_list ::= "{" option_def_list "}"

     option_def_list_content ::= 
                            | not_empty_option_def_list

     not_empty_option_def_list ::= option_def_entry
                              | not_empty_option_def_list "," option_def_entry
                              | not_empty_option_def_list ","

     option_def_entry ::= "{" option_def_params "}"

     sub_option_def ::= "{" option_def_params "}"

     option_def_params ::= 
                      | not_empty_option_def_params

     not_empty_option_def_params ::= option_def_param
                                | not_empty_option_def_params "," option_def_param
                                | not_empty_option_def_params ","

     option_def_param ::= option_def_name
                     | option_def_code
                     | option_def_type
                     | option_def_record_types
                     | option_def_space
                     | option_def_encapsulate
                     | option_def_array
                     | user_context
                     | comment
                     | unknown_map_entry

     option_def_name ::= name

     code ::= "code" ":" INTEGER

     option_def_code ::= code

     option_def_type ::= "type" ":" STRING

     option_def_record_types ::= "record-types" ":" STRING

     space ::= "space" ":" STRING

     option_def_space ::= space

     option_def_encapsulate ::= "encapsulate" ":" STRING

     option_def_array ::= "array" ":" BOOLEAN

     option_data_list ::= "option-data" ":" "[" option_data_list_content "]"

     option_data_list_content ::= 
                             | not_empty_option_data_list

     not_empty_option_data_list ::= option_data_entry
                               | not_empty_option_data_list "," option_data_entry
                               | not_empty_option_data_list ","

     option_data_entry ::= "{" option_data_params "}"

     sub_option_data ::= "{" option_data_params "}"

     option_data_params ::= 
                       | not_empty_option_data_params

     not_empty_option_data_params ::= option_data_param
                                 | not_empty_option_data_params "," option_data_param
                                 | not_empty_option_data_params ","

     option_data_param ::= option_data_name
                      | option_data_data
                      | option_data_code
                      | option_data_space
                      | option_data_csv_format
                      | option_data_always_send
                      | user_context
                      | comment
                      | unknown_map_entry

     option_data_name ::= name

     option_data_data ::= "data" ":" STRING

     option_data_code ::= code

     option_data_space ::= space

     option_data_csv_format ::= "csv-format" ":" BOOLEAN

     option_data_always_send ::= "always-send" ":" BOOLEAN

     pools_list ::= "pools" ":" "[" pools_list_content "]"

     pools_list_content ::= 
                       | not_empty_pools_list

     not_empty_pools_list ::= pool_list_entry
                         | not_empty_pools_list "," pool_list_entry
                         | not_empty_pools_list ","

     pool_list_entry ::= "{" pool_params "}"

     sub_pool4 ::= "{" pool_params "}"

     pool_params ::= pool_param
                | pool_params "," pool_param
                | pool_params ","

     pool_param ::= pool_entry
               | option_data_list
               | client_class
               | require_client_classes
               | user_context
               | comment
               | unknown_map_entry

     pool_entry ::= "pool" ":" STRING

     user_context ::= "user-context" ":" map_value

     comment ::= "comment" ":" STRING

     reservations ::= "reservations" ":" "[" reservations_list "]"

     reservations_list ::= 
                      | not_empty_reservations_list

     not_empty_reservations_list ::= reservation
                                | not_empty_reservations_list "," reservation
                                | not_empty_reservations_list ","

     reservation ::= "{" reservation_params "}"

     sub_reservation ::= "{" reservation_params "}"

     reservation_params ::= 
                       | not_empty_reservation_params

     not_empty_reservation_params ::= reservation_param
                                 | not_empty_reservation_params "," reservation_param
                                 | not_empty_reservation_params ","

     reservation_param ::= duid
                      | reservation_client_classes
                      | client_id_value
                      | circuit_id_value
                      | flex_id_value
                      | ip_address
                      | hw_address
                      | hostname
                      | option_data_list
                      | next_server
                      | server_hostname
                      | boot_file_name
                      | user_context
                      | comment
                      | unknown_map_entry

     next_server ::= "next-server" ":" STRING

     server_hostname ::= "server-hostname" ":" STRING

     boot_file_name ::= "boot-file-name" ":" STRING

     ip_address ::= "ip-address" ":" STRING

     ip_addresses ::= "ip-addresses" ":" list_strings

     duid ::= "duid" ":" STRING

     hw_address ::= "hw-address" ":" STRING

     client_id_value ::= "client-id" ":" STRING

     circuit_id_value ::= "circuit-id" ":" STRING

     flex_id_value ::= "flex-id" ":" STRING

     hostname ::= "hostname" ":" STRING

     reservation_client_classes ::= "client-classes" ":" list_strings

     relay ::= "relay" ":" "{" relay_map "}"

     relay_map ::= ip_address
              | ip_addresses

     client_classes ::= "client-classes" ":" "[" client_classes_list "]"

     client_classes_list ::= client_class_entry
                        | client_classes_list "," client_class_entry
                        | client_classes_list ","

     client_class_entry ::= "{" client_class_params "}"

     client_class_params ::= 
                        | not_empty_client_class_params

     not_empty_client_class_params ::= client_class_param
                                  | not_empty_client_class_params "," client_class_param
                                  | not_empty_client_class_params ","

     client_class_param ::= client_class_name
                       | client_class_test
                       | only_if_required
                       | option_def_list
                       | option_data_list
                       | next_server
                       | server_hostname
                       | boot_file_name
                       | user_context
                       | comment
                       | unknown_map_entry
                       | valid_lifetime
                       | min_valid_lifetime
                       | max_valid_lifetime

     client_class_name ::= name

     client_class_test ::= "test" ":" STRING

     only_if_required ::= "only-if-required" ":" BOOLEAN

     dhcp4o6_port ::= "dhcp4o6-port" ":" INTEGER

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

     dhcp_queue_control ::= "dhcp-queue-control" ":" "{" queue_control_params "}"

     queue_control_params ::= queue_control_param
                         | queue_control_params "," queue_control_param
                         | queue_control_params ","

     queue_control_param ::= enable_queue
                        | queue_type
                        | capacity
                        | user_context
                        | comment
                        | arbitrary_map_entry

     enable_queue ::= "enable-queue" ":" BOOLEAN

     queue_type ::= "queue-type" ":" STRING

     capacity ::= "capacity" ":" INTEGER

     arbitrary_map_entry ::= STRING ":" value

     dhcp_ddns ::= "dhcp-ddns" ":" "{" dhcp_ddns_params "}"

     sub_dhcp_ddns ::= "{" dhcp_ddns_params "}"

     dhcp_ddns_params ::= dhcp_ddns_param
                     | dhcp_ddns_params "," dhcp_ddns_param
                     | dhcp_ddns_params ","

     dhcp_ddns_param ::= enable_updates
                    | server_ip
                    | server_port
                    | sender_ip
                    | sender_port
                    | max_queue_size
                    | ncr_protocol
                    | ncr_format
                    | dep_override_no_update
                    | dep_override_client_update
                    | dep_replace_client_name
                    | dep_generated_prefix
                    | dep_qualifying_suffix
                    | dep_hostname_char_set
                    | dep_hostname_char_replacement
                    | user_context
                    | comment
                    | unknown_map_entry

     enable_updates ::= "enable-updates" ":" BOOLEAN

     server_ip ::= "server-ip" ":" STRING

     server_port ::= "server-port" ":" INTEGER

     sender_ip ::= "sender-ip" ":" STRING

     sender_port ::= "sender-port" ":" INTEGER

     max_queue_size ::= "max-queue-size" ":" INTEGER

     ncr_protocol ::= "ncr-protocol" ":" ncr_protocol_value

     ncr_protocol_value ::= "udp"
                       | "tcp"

     ncr_format ::= "ncr-format" ":" "JSON"

     dep_qualifying_suffix ::= "qualifying-suffix" ":" STRING

     dep_override_no_update ::= "override-no-update" ":" BOOLEAN

     dep_override_client_update ::= "override-client-update" ":" BOOLEAN

     dep_replace_client_name ::= "replace-client-name" ":" ddns_replace_client_name_value

     dep_generated_prefix ::= "generated-prefix" ":" STRING

     dep_hostname_char_set ::= "hostname-char-set" ":" STRING

     dep_hostname_char_replacement ::= "hostname-char-replacement" ":" STRING

     config_control ::= "config-control" ":" "{" config_control_params "}"

     sub_config_control ::= "{" config_control_params "}"

     config_control_params ::= config_control_param
                          | config_control_params "," config_control_param
                          | config_control_params ","

     config_control_param ::= config_databases
                         | config_fetch_wait_time

     config_databases ::= "config-databases" ":" "[" database_list "]"

     config_fetch_wait_time ::= "config-fetch-wait-time" ":" INTEGER

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

     compatibility ::= "compatibility" ":" "{" compatibility_params "}"

     compatibility_params ::= compatibility_param
                         | compatibility_params "," compatibility_param
                         | compatibility_params ","

     compatibility_param ::= lenient_option_parsing
                        | unknown_map_entry

     lenient_option_parsing ::= "lenient-option-parsing" ":" BOOLEAN

