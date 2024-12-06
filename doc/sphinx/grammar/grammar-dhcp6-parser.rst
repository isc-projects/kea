This grammar is generated from ``dhcp6_parser.yy``. See :ref:`dhcp6` for more details.

.. code-block:: BNF
   :linenos:

     Grammar

     $accept ::= start EOF

     start ::= TOPLEVEL_JSON sub_json

     start ::= TOPLEVEL_DHCP6 syntax_map

     start ::= SUB_DHCP6 sub_dhcp6

     start ::= SUB_INTERFACES6 sub_interfaces6

     start ::= SUB_SUBNET6 sub_subnet6

     start ::= SUB_POOL6 sub_pool6

     start ::= SUB_PD_POOL sub_pd_pool

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

     global_object ::= "Dhcp6" ":" "{" global_params "}"
                  | global_object_comma

     global_object_comma ::= global_object ","

     sub_dhcp6 ::= "{" global_params "}"

     global_params ::= global_param
                  | global_params "," global_param
                  | global_params ","

     global_param ::= data_directory
                 | preferred_lifetime
                 | min_preferred_lifetime
                 | max_preferred_lifetime
                 | valid_lifetime
                 | min_valid_lifetime
                 | max_valid_lifetime
                 | renew_timer
                 | rebind_timer
                 | decline_probation_period
                 | subnet6_list
                 | shared_networks
                 | interfaces_config
                 | lease_database
                 | hosts_database
                 | hosts_databases
                 | mac_sources
                 | relay_supplied_options
                 | host_reservation_identifiers
                 | client_classes
                 | option_def_list
                 | option_data_list
                 | hooks_libraries
                 | expired_leases_processing
                 | server_id
                 | dhcp4o6_port
                 | control_socket
                 | control_sockets
                 | dhcp_queue_control
                 | dhcp_ddns
                 | user_context
                 | comment
                 | sanity_checks
                 | reservations
                 | config_control
                 | server_tag
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
                 | ddns_conflict_resolution_mode
                 | ddns_ttl_percent
                 | store_extended_info
                 | statistic_default_sample_count
                 | statistic_default_sample_age
                 | dhcp_multi_threading
                 | early_global_reservations_lookup
                 | ip_reservations_unique
                 | reservations_lookup_first
                 | compatibility
                 | parked_packet_limit
                 | allocator
                 | pd_allocator
                 | unknown_map_entry

     data_directory ::= "data-directory" ":" STRING

     preferred_lifetime ::= "preferred-lifetime" ":" INTEGER

     min_preferred_lifetime ::= "min-preferred-lifetime" ":" INTEGER

     max_preferred_lifetime ::= "max-preferred-lifetime" ":" INTEGER

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

     ddns_conflict_resolution_mode ::= "ddns-conflict-resolution-mode" ":" ddns_conflict_resolution_mode_value

     ddns_conflict_resolution_mode_value ::= "check-with-dhcid"
                                        | "no-check-with-dhcid"
                                        | "check-exists-with-dhcid"
                                        | "no-check-without-dhcid"

     ddns_ttl_percent ::= "ddns-ttl-percent" ":" FLOAT

     hostname_char_set ::= "hostname-char-set" ":" STRING

     hostname_char_replacement ::= "hostname-char-replacement" ":" STRING

     store_extended_info ::= "store-extended-info" ":" BOOLEAN

     statistic_default_sample_count ::= "statistic-default-sample-count" ":" INTEGER

     statistic_default_sample_age ::= "statistic-default-sample-age" ":" INTEGER

     server_tag ::= "server-tag" ":" STRING

     parked_packet_limit ::= "parked-packet-limit" ":" INTEGER

     allocator ::= "allocator" ":" STRING

     pd_allocator ::= "pd-allocator" ":" STRING

     early_global_reservations_lookup ::= "early-global-reservations-lookup" ":" BOOLEAN

     ip_reservations_unique ::= "ip-reservations-unique" ":" BOOLEAN

     reservations_lookup_first ::= "reservations-lookup-first" ":" BOOLEAN

     interfaces_config ::= "interfaces-config" ":" "{" interfaces_config_params "}"

     sub_interfaces6 ::= "{" interfaces_config_params "}"

     interfaces_config_params ::= interfaces_config_param
                             | interfaces_config_params "," interfaces_config_param
                             | interfaces_config_params ","

     interfaces_config_param ::= interfaces_list
                            | re_detect
                            | service_sockets_require_all
                            | service_sockets_retry_wait_time
                            | service_sockets_max_retries
                            | user_context
                            | comment
                            | unknown_map_entry

     interfaces_list ::= "interfaces" ":" list_strings

     re_detect ::= "re-detect" ":" BOOLEAN

     service_sockets_require_all ::= "service-sockets-require-all" ":" BOOLEAN

     service_sockets_retry_wait_time ::= "service-sockets-retry-wait-time" ":" INTEGER

     service_sockets_max_retries ::= "service-sockets-max-retries" ":" INTEGER

     lease_database ::= "lease-database" ":" "{" database_map_params "}"

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
                       | read_timeout
                       | write_timeout
                       | tcp_user_timeout
                       | max_reconnect_tries
                       | reconnect_wait_time
                       | on_fail
                       | retry_on_startup
                       | max_row_errors
                       | trust_anchor
                       | cert_file
                       | key_file
                       | cipher_list
                       | unknown_map_entry

     database_type ::= "type" ":" STRING

     user ::= "user" ":" STRING

     password ::= "password" ":" STRING

     host ::= "host" ":" STRING

     port ::= "port" ":" INTEGER

     name ::= "name" ":" STRING

     persist ::= "persist" ":" BOOLEAN

     lfc_interval ::= "lfc-interval" ":" INTEGER

     readonly ::= "readonly" ":" BOOLEAN

     connect_timeout ::= "connect-timeout" ":" INTEGER

     read_timeout ::= "read-timeout" ":" INTEGER

     write_timeout ::= "write-timeout" ":" INTEGER

     tcp_user_timeout ::= "tcp-user-timeout" ":" INTEGER

     reconnect_wait_time ::= "reconnect-wait-time" ":" INTEGER

     on_fail ::= "on-fail" ":" on_fail_mode

     on_fail_mode ::= "stop-retry-exit"
                 | "serve-retry-exit"
                 | "serve-retry-continue"

     retry_on_startup ::= "retry-on-startup" ":" BOOLEAN

     max_row_errors ::= "max-row-errors" ":" INTEGER

     max_reconnect_tries ::= "max-reconnect-tries" ":" INTEGER

     trust_anchor ::= "trust-anchor" ":" STRING

     cert_file ::= "cert-file" ":" STRING

     key_file ::= "key-file" ":" STRING

     cipher_list ::= "cipher-list" ":" STRING

     sanity_checks ::= "sanity-checks" ":" "{" sanity_checks_params "}"

     sanity_checks_params ::= sanity_checks_param
                         | sanity_checks_params "," sanity_checks_param
                         | sanity_checks_params ","

     sanity_checks_param ::= lease_checks
                        | extended_info_checks

     lease_checks ::= "lease-checks" ":" STRING

     extended_info_checks ::= "extended-info-checks" ":" STRING

     mac_sources ::= "mac-sources" ":" "[" mac_sources_list "]"

     mac_sources_list ::= mac_sources_value
                     | mac_sources_list "," mac_sources_value
                     | mac_sources_list ","

     mac_sources_value ::= duid_id
                      | string_id

     duid_id ::= "duid"

     string_id ::= STRING

     host_reservation_identifiers ::= "host-reservation-identifiers" ":" "[" host_reservation_identifiers_list "]"

     host_reservation_identifiers_list ::= host_reservation_identifier
                                      | host_reservation_identifiers_list "," host_reservation_identifier
                                      | host_reservation_identifiers_list ","

     host_reservation_identifier ::= duid_id
                                | hw_address_id
                                | flex_id

     hw_address_id ::= "hw-address"

     flex_id ::= "flex-id"

     relay_supplied_options ::= "relay-supplied-options" ":" "[" list_content "]"

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

     subnet6_list ::= "subnet6" ":" "[" subnet6_list_content "]"

     subnet6_list_content ::= 
                         | not_empty_subnet6_list

     not_empty_subnet6_list ::= subnet6
                           | not_empty_subnet6_list "," subnet6
                           | not_empty_subnet6_list ","

     subnet6 ::= "{" subnet6_params "}"

     sub_subnet6 ::= "{" subnet6_params "}"

     subnet6_params ::= subnet6_param
                   | subnet6_params "," subnet6_param
                   | subnet6_params ","

     subnet6_param ::= preferred_lifetime
                  | min_preferred_lifetime
                  | max_preferred_lifetime
                  | valid_lifetime
                  | min_valid_lifetime
                  | max_valid_lifetime
                  | renew_timer
                  | rebind_timer
                  | option_data_list
                  | pools_list
                  | pd_pools_list
                  | subnet
                  | interface
                  | interface_id
                  | id
                  | rapid_commit
                  | client_class
                  | network_client_classes
                  | require_client_classes
                  | evaluate_additional_classes
                  | reservations
                  | reservations_global
                  | reservations_in_subnet
                  | reservations_out_of_pool
                  | relay
                  | user_context
                  | comment
                  | calculate_tee_times
                  | t1_percent
                  | t2_percent
                  | cache_threshold
                  | cache_max_age
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
                  | ddns_conflict_resolution_mode
                  | ddns_ttl_percent
                  | store_extended_info
                  | allocator
                  | pd_allocator
                  | unknown_map_entry

     subnet ::= "subnet" ":" STRING

     interface ::= "interface" ":" STRING

     interface_id ::= "interface-id" ":" STRING

     client_class ::= "client-class" ":" STRING

     network_client_classes ::= "client-classes" ":" list_strings

     require_client_classes ::= "require-client-classes" ":" list_strings

     evaluate_additional_classes ::= "evaluate-additional-classes" ":" list_strings

     reservations_global ::= "reservations-global" ":" BOOLEAN

     reservations_in_subnet ::= "reservations-in-subnet" ":" BOOLEAN

     reservations_out_of_pool ::= "reservations-out-of-pool" ":" BOOLEAN

     id ::= "id" ":" INTEGER

     rapid_commit ::= "rapid-commit" ":" BOOLEAN

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
                         | subnet6_list
                         | interface
                         | interface_id
                         | renew_timer
                         | rebind_timer
                         | option_data_list
                         | relay
                         | reservations_global
                         | reservations_in_subnet
                         | reservations_out_of_pool
                         | client_class
                         | network_client_classes
                         | require_client_classes
                         | evaluate_additional_classes
                         | preferred_lifetime
                         | min_preferred_lifetime
                         | max_preferred_lifetime
                         | rapid_commit
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
                         | ddns_conflict_resolution_mode
                         | ddns_ttl_percent
                         | store_extended_info
                         | allocator
                         | pd_allocator
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
                      | option_data_never_send
                      | user_context
                      | comment
                      | option_data_client_classes
                      | unknown_map_entry

     option_data_name ::= name

     option_data_data ::= "data" ":" STRING

     option_data_code ::= code

     option_data_space ::= space

     option_data_csv_format ::= "csv-format" ":" BOOLEAN

     option_data_always_send ::= "always-send" ":" BOOLEAN

     option_data_never_send ::= "never-send" ":" BOOLEAN

     option_data_client_classes ::= "client-classes" ":" list_strings

     pools_list ::= "pools" ":" "[" pools_list_content "]"

     pools_list_content ::= 
                       | not_empty_pools_list

     not_empty_pools_list ::= pool_list_entry
                         | not_empty_pools_list "," pool_list_entry
                         | not_empty_pools_list ","

     pool_list_entry ::= "{" pool_params "}"

     sub_pool6 ::= "{" pool_params "}"

     pool_params ::= pool_param
                | pool_params "," pool_param
                | pool_params ","

     pool_param ::= pool_entry
               | pool_id
               | option_data_list
               | client_class
               | network_client_classes
               | require_client_classes
               | evaluate_additional_classes
               | user_context
               | comment
               | unknown_map_entry

     pool_entry ::= "pool" ":" STRING

     pool_id ::= "pool-id" ":" INTEGER

     user_context ::= "user-context" ":" map_value

     comment ::= "comment" ":" STRING

     pd_pools_list ::= "pd-pools" ":" "[" pd_pools_list_content "]"

     pd_pools_list_content ::= 
                          | not_empty_pd_pools_list

     not_empty_pd_pools_list ::= pd_pool_entry
                            | not_empty_pd_pools_list "," pd_pool_entry
                            | not_empty_pd_pools_list ","

     pd_pool_entry ::= "{" pd_pool_params "}"

     sub_pd_pool ::= "{" pd_pool_params "}"

     pd_pool_params ::= pd_pool_param
                   | pd_pool_params "," pd_pool_param
                   | pd_pool_params ","

     pd_pool_param ::= pd_prefix
                  | pd_prefix_len
                  | pd_delegated_len
                  | pool_id
                  | option_data_list
                  | client_class
                  | network_client_classes
                  | require_client_classes
                  | evaluate_additional_classes
                  | excluded_prefix
                  | excluded_prefix_len
                  | user_context
                  | comment
                  | unknown_map_entry

     pd_prefix ::= "prefix" ":" STRING

     pd_prefix_len ::= "prefix-len" ":" INTEGER

     excluded_prefix ::= "excluded-prefix" ":" STRING

     excluded_prefix_len ::= "excluded-prefix-len" ":" INTEGER

     pd_delegated_len ::= "delegated-len" ":" INTEGER

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
                      | ip_addresses
                      | prefixes
                      | excluded_prefixes
                      | hw_address
                      | hostname
                      | flex_id_value
                      | option_data_list
                      | user_context
                      | comment
                      | unknown_map_entry

     ip_addresses ::= "ip-addresses" ":" list_strings

     prefixes ::= "prefixes" ":" list_strings

     excluded_prefixes ::= "excluded-prefixes" ":" list_strings

     duid ::= "duid" ":" STRING

     hw_address ::= "hw-address" ":" STRING

     hostname ::= "hostname" ":" STRING

     flex_id_value ::= "flex-id" ":" STRING

     reservation_client_classes ::= "client-classes" ":" list_strings

     relay ::= "relay" ":" "{" relay_map "}"

     relay_map ::= ip_addresses

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
                       | client_class_template_test
                       | only_if_required
                       | only_in_additional_list
                       | option_data_list
                       | user_context
                       | comment
                       | preferred_lifetime
                       | min_preferred_lifetime
                       | max_preferred_lifetime
                       | valid_lifetime
                       | min_valid_lifetime
                       | max_valid_lifetime
                       | unknown_map_entry

     client_class_name ::= name

     client_class_test ::= "test" ":" STRING

     client_class_template_test ::= "template-test" ":" STRING

     only_if_required ::= "only-if-required" ":" BOOLEAN

     only_in_additional_list ::= "only-in-additional-list" ":" BOOLEAN

     server_id ::= "server-id" ":" "{" server_id_params "}"

     server_id_params ::= server_id_param
                     | server_id_params "," server_id_param
                     | server_id_params ","

     server_id_param ::= server_id_type
                    | identifier
                    | time
                    | htype
                    | enterprise_id
                    | persist
                    | user_context
                    | comment
                    | unknown_map_entry

     server_id_type ::= "type" ":" duid_type

     duid_type ::= "LLT"
              | "EN"
              | "LL"

     htype ::= "htype" ":" INTEGER

     identifier ::= "identifier" ":" STRING

     time ::= "time" ":" INTEGER

     enterprise_id ::= "enterprise-id" ":" INTEGER

     dhcp4o6_port ::= "dhcp4o6-port" ":" INTEGER

     control_socket ::= "control-socket" ":" "{" control_socket_params "}"

     control_sockets ::= "control-sockets" ":" "[" control_socket_list "]"

     control_socket_list ::= 
                        | not_empty_control_socket_list

     not_empty_control_socket_list ::= control_socket_entry
                                  | not_empty_control_socket_list "," control_socket_entry
                                  | not_empty_control_socket_list ","

     control_socket_entry ::= "{" control_socket_params "}"

     control_socket_params ::= control_socket_param
                          | control_socket_params "," control_socket_param
                          | control_socket_params ","

     control_socket_param ::= control_socket_type
                         | control_socket_name
                         | control_socket_address
                         | control_socket_port
                         | authentication
                         | trust_anchor
                         | cert_file
                         | key_file
                         | cert_required
                         | http_headers
                         | user_context
                         | comment
                         | unknown_map_entry

     control_socket_type ::= "socket-type" ":" control_socket_type_value

     control_socket_type_value ::= "unix"
                              | "http"
                              | "https"

     control_socket_name ::= "socket-name" ":" STRING

     control_socket_address ::= "socket-address" ":" STRING

     control_socket_port ::= "socket-port" ":" INTEGER

     cert_required ::= "cert-required" ":" BOOLEAN

     http_headers ::= "http-headers" ":" "[" http_header_list "]"

     http_header_list ::= 
                     | not_empty_http_header_list

     not_empty_http_header_list ::= http_header
                               | not_empty_http_header_list "," http_header
                               | not_empty_http_header_list ","

     http_header ::= "{" http_header_params "}"

     http_header_params ::= http_header_param
                       | http_header_params "," http_header_param
                       | http_header_params ","

     http_header_param ::= name
                      | header_value
                      | user_context
                      | comment
                      | unknown_map_entry

     header_value ::= "value" ":" STRING

     authentication ::= "authentication" ":" "{" auth_params "}"

     auth_params ::= auth_param
                | auth_params "," auth_param
                | auth_params ","

     auth_param ::= auth_type
               | realm
               | directory
               | clients
               | comment
               | user_context
               | unknown_map_entry

     auth_type ::= "type" ":" auth_type_value

     auth_type_value ::= "basic"

     realm ::= "realm" ":" STRING

     directory ::= "directory" ":" STRING

     clients ::= "clients" ":" "[" clients_list "]"

     clients_list ::= 
                 | not_empty_clients_list

     not_empty_clients_list ::= basic_auth
                           | not_empty_clients_list "," basic_auth
                           | not_empty_clients_list ","

     basic_auth ::= "{" clients_params "}"

     clients_params ::= clients_param
                   | clients_params "," clients_param
                   | clients_params ","

     clients_param ::= user
                  | user_file
                  | password
                  | password_file
                  | user_context
                  | comment
                  | unknown_map_entry

     user_file ::= "user-file" ":" STRING

     password_file ::= "password-file" ":" STRING

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

     ncr_protocol_value ::= "UDP"
                       | "TCP"

     ncr_format ::= "ncr-format" ":" "JSON"

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

     output_options_list ::= "output-options" ":" "[" output_options_list_content "]"

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

