sources = [
  'alloc_engine.cc',
  'alloc_engine.h',
  'alloc_engine_log.cc',
  'alloc_engine_log.h',
  'assignable_network.h',
  'base_host_data_source.h',
  'cache_host_data_source.h',
  'callout_handle_store.h',
  'cfg_4o6.cc',
  'cfg_4o6.h',
  'cfg_consistency.cc',
  'cfg_consistency.h',
  'cfg_db_access.cc',
  'cfg_db_access.h',
  'cfg_duid.cc',
  'cfg_duid.h',
  'cfg_hosts.cc',
  'cfg_hosts.h',
  'cfg_hosts_util.cc',
  'cfg_hosts_util.h',
  'cfg_iface.cc',
  'cfg_iface.h',
  'cfg_expiration.cc',
  'cfg_expiration.h',
  'cfg_host_operations.cc',
  'cfg_host_operations.h',
  'cfg_option.cc',
  'cfg_option.h',
  'cfg_option_def.cc',
  'cfg_option_def.h',
  'cfg_rsoo.cc',
  'cfg_rsoo.h',
  'cfg_shared_networks.cc',
  'cfg_shared_networks.h',
  'cfg_subnets4.cc',
  'cfg_subnets4.h',
  'cfg_subnets6.cc',
  'cfg_subnets6.h',
  'cfg_mac_source.cc',
  'cfg_mac_source.h',
  'cfgmgr.cc',
  'cfgmgr.h',
  'client_class_def.cc',
  'client_class_def.h',
  'config_backend_dhcp4.h',
  'config_backend_pool_dhcp4.cc',
  'config_backend_pool_dhcp4.h',
  'config_backend_dhcp4_mgr.cc',
  'config_backend_dhcp4_mgr.h',
  'csv_lease_file4.cc',
  'csv_lease_file4.h',
  'csv_lease_file6.cc',
  'csv_lease_file6.h',
  'd2_client_cfg.cc',
  'd2_client_cfg.h',
  'd2_client_mgr.cc',
  'd2_client_mgr.h',
  'db_type.h',
  'dhcp4o6_ipc.cc',
  'dhcp4o6_ipc.h',
  'dhcpsrv_exceptions.h',
  'dhcpsrv_log.cc',
  'dhcpsrv_log.h',
  'host.cc',
  'host.h',
  'host_container.h',
  'host_data_source_factory.cc',
  'host_data_source_factory.h',
  'host_mgr.cc',
  'host_mgr.h',
  'hosts_log.cc',
  'hosts_log.h',
  'key_from_key.h',
  'lease.cc',
  'lease.h',
  'lease_file_loader.h',
  'lease_file_stats.h',
  'lease_mgr.cc',
  'lease_mgr.h',
  'lease_mgr_factory.cc',
  'lease_mgr_factory.h',
  'memfile_lease_mgr.cc',
  'memfile_lease_mgr.h',
  'memfile_lease_storage.h',
  'pool.cc',
  'pool.h',
  'sanity_checker.cc',
  'sanity_checker.h',
  'shared_network.cc',
  'shared_network.h',
  'srv_config.cc',
  'srv_config.h',
  'subnet.cc',
  'subnet.h',
  'subnet_id.h',
  'subnet_selector.h',
  'timer_mgr.cc',
  'timer_mgr.h',
  'triplet.h',
  'utils.h',
  'writable_host_data_source.h',
# Configuration parsers',
  'parsers/client_class_def_parser.cc',
  'parsers/client_class_def_parser.h',
  'parsers/dhcp_parsers.cc',
  'parsers/dhcp_parsers.h',
  'parsers/duid_config_parser.cc',
  'parsers/duid_config_parser.h',
  'parsers/expiration_config_parser.cc',
  'parsers/expiration_config_parser.h',
  'parsers/host_reservation_parser.cc',
  'parsers/host_reservation_parser.h',
  'parsers/host_reservations_list_parser.h',
  'parsers/ifaces_config_parser.cc',
  'parsers/ifaces_config_parser.h',
  'parsers/option_data_parser.cc',
  'parsers/option_data_parser.h',
  'parsers/dhcp_queue_control_parser.cc',
  'parsers/dhcp_queue_control_parser.h',
  'parsers/sanity_checks_parser.cc',
  'parsers/sanity_checks_parser.h',
  'parsers/shared_network_parser.cc',
  'parsers/shared_network_parser.h',
  'parsers/shared_networks_list_parser.h',
  'parsers/simple_parser4.cc',
  'parsers/simple_parser4.h',
  'parsers/simple_parser6.cc',
  'parsers/simple_parser6.h']

# if HAVE_MYSQL
# libkea_dhcpsrv_la_SOURCES += mysql_lease_mgr.cc mysql_lease_mgr.h
# libkea_dhcpsrv_la_SOURCES += mysql_host_data_source.cc mysql_host_data_source.h
# endif

# libkea_dhcpsrv_la_SOURCES += ncr_generator.cc ncr_generator.h
# libkea_dhcpsrv_la_SOURCES += network.cc network.h
# libkea_dhcpsrv_la_SOURCES += network_state.cc network_state.h

# if HAVE_PGSQL
# libkea_dhcpsrv_la_SOURCES += pgsql_host_data_source.cc pgsql_host_data_source.h
# libkea_dhcpsrv_la_SOURCES += pgsql_lease_mgr.cc pgsql_lease_mgr.h
# endif

# if HAVE_CQL
# libkea_dhcpsrv_la_SOURCES += cql_host_data_source.cc cql_host_data_source.h
# libkea_dhcpsrv_la_SOURCES += cql_lease_mgr.cc cql_lease_mgr.h
# endif


alloc_engine_messages_ch = custom_target('alloc_engine_messages.[ch]',
                                         output : ['alloc_engine_messages.cc',
                                                   'alloc_engine_messages.h'],
                                         input : 'alloc_engine_messages.mes',
                                         command : [kea_msg_compiler, '-d', meson.current_build_dir(), '@INPUT@'])
dhcpsrv_messages_ch = custom_target('dhcpsrv_messages.[ch]',
                                    output : ['dhcpsrv_messages.cc',
                                              'dhcpsrv_messages.h'],
                                    input : 'dhcpsrv_messages.mes',
                                    command : [kea_msg_compiler, '-d', meson.current_build_dir(), '@INPUT@'])
hosts_messages_ch = custom_target('hosts_messages.[ch]',
                                  output : ['hosts_messages.cc',
                                            'hosts_messages.h'],
                                  input : 'hosts_messages.mes',
                                  command : [kea_msg_compiler, '-d', meson.current_build_dir(), '@INPUT@'])

sources += alloc_engine_messages_ch
sources += dhcpsrv_messages_ch
sources += hosts_messages_ch



dhcpsrv_lib = static_library('kea-dhcpsrv',
                             sources,
                             cpp_args : ['-DKEA_LFC_EXECUTABLE="' + join_paths(get_option('prefix'), 'sbin/kea-lfc"'),
                                         '-DDHCP_DATA_DIR="' + join_paths(get_option('prefix'), get_option('localstatedir')) + '"'],  # add @PACKAGE@
                             include_directories : [lib_inc, configuration_inc],
                             install : true)
