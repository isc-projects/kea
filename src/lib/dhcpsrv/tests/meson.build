if not TESTS_OPT.enabled()
    subdir_done()
endif

current_build_dir = meson.current_build_dir()
libs_testutils = [
    kea_dhcpsrv_testutils_lib,
    kea_dhcp_testutils_lib,
    kea_database_testutils_lib,
    kea_testutils_lib,
]
configure_file(
    input: 'test_kea_lfc_env.sh.in',
    output: 'test_kea_lfc_env.sh',
    copy: true,
)
kea_dhcpsrv_conf_data = configuration_data()
kea_dhcpsrv_conf_data.set('abs_builddir', current_build_dir)
kea_dhcpsrv_conf_data.set('dotlibs', '')
configure_file(
    input: 'test_libraries.h.in',
    output: 'test_libraries.h',
    configuration: kea_dhcpsrv_conf_data,
)
co1 = shared_library(
    'co1',
    'callout_library.cc',
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
    build_rpath: '/nowhere',
    name_suffix: 'so',
)
co2 = shared_library(
    'co2',
    'callout_library.cc',
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
    build_rpath: '/nowhere',
    name_suffix: 'so',
)
co3 = shared_library(
    'co3',
    'callout_params_library.cc',
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
    build_rpath: '/nowhere',
    name_suffix: 'so',
)

sources = [
    'alloc_engine4_unittest.cc',
    'alloc_engine6_unittest.cc',
    'alloc_engine_expiration_unittest.cc',
    'alloc_engine_hooks_unittest.cc',
    'allocation_state_unittest.cc',
    'legal_log_mgr_factory_unittest.cc',
    'callout_handle_store_unittest.cc',
    'cb_ctl_dhcp_unittest.cc',
    'cfg_db_access_unittest.cc',
    'cfg_duid_unittest.cc',
    'cfg_expiration_unittest.cc',
    'cfg_host_operations_unittest.cc',
    'cfg_hosts_unittest.cc',
    'cfg_iface_unittest.cc',
    'cfg_mac_source_unittest.cc',
    'cfg_multi_threading_unittest.cc',
    'cfg_option_def_unittest.cc',
    'cfg_option_unittest.cc',
    'cfg_rsoo_unittest.cc',
    'cfg_shared_networks4_unittest.cc',
    'cfg_shared_networks6_unittest.cc',
    'cfg_subnets4_unittest.cc',
    'cfg_subnets6_unittest.cc',
    'cfgmgr_unittest.cc',
    'client_class_def_parser_unittest.cc',
    'client_class_def_unittest.cc',
    'csv_lease_file4_unittest.cc',
    'csv_lease_file6_unittest.cc',
    'd2_client_unittest.cc',
    'd2_udp_unittest.cc',
    'dhcp4o6_ipc_unittest.cc',
    'dhcp_parsers_unittest.cc',
    'dhcp_queue_control_parser_unittest.cc',
    'duid_config_parser_unittest.cc',
    'expiration_config_parser_unittest.cc',
    'flq_allocation_state_unittest.cc',
    'flq_allocator_unittest.cc',
    'host_cache_unittest.cc',
    'host_data_source_factory_unittest.cc',
    'host_mgr_unittest.cc',
    'host_reservation_parser_unittest.cc',
    'host_reservations_list_parser_unittest.cc',
    'host_unittest.cc',
    'ifaces_config_parser_unittest.cc',
    'ip_range_permutation_unittest.cc',
    'ip_range_unittest.cc',
    'iterative_allocation_state_unittest.cc',
    'iterative_allocator_unittest.cc',
    'lease_file_loader_unittest.cc',
    'lease_mgr_factory_unittest.cc',
    'lease_mgr_unittest.cc',
    'lease_unittest.cc',
    'memfile_lease_extended_info_unittest.cc',
    'memfile_lease_limits_unittest.cc',
    'memfile_lease_mgr_unittest.cc',
    'multi_threading_config_parser_unittest.cc',
    'ncr_generator_unittest.cc',
    'network_state_unittest.cc',
    'network_unittest.cc',
    'pool_unittest.cc',
    'random_allocation_state_unittest.cc',
    'random_allocator_unittest.cc',
    'resource_handler_unittest.cc',
    'run_unittests.cc',
    'sanity_checks_unittest.cc',
    'shared_network_parser_unittest.cc',
    'shared_network_unittest.cc',
    'shared_networks_list_parser_unittest.cc',
    'srv_config_unittest.cc',
    'subnet_unittest.cc',
    'test_get_callout_handle.cc',
    'timer_mgr_unittest.cc',
    'tracking_lease_mgr_unittest.cc',
]
if FUZZ_OPT.enabled()
    sources += ['packet_fuzzer_unittest.cc']
endif
kea_dhcpsrv_tests = executable(
    'kea-dhcpsrv-tests',
    sources,
    cpp_args: [
        f'-DTEST_DATA_BUILDDIR="@current_build_dir@"',
        f'-DDHCP_DATA_DIR="@current_build_dir@"',
        f'-DKEA_LFC_BUILD_DIR="@KEA_LFC_BUILT@"',
        f'-DDEFAULT_HOOKS_PATH="@DEFAULT_HOOKS_PATH@"',
    ],
    dependencies: [CRYPTO_DEP, GTEST_DEP],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: [kea_util_unittests_lib, libs_testutils] + LIBS_BUILT_SO_FAR,
)
test(
    'kea-dhcpsrv-tests',
    kea_dhcpsrv_tests,
    depends: [co1, co2, co3],
    protocol: 'gtest',
    is_parallel: false,
    priority: -1,
    timeout: 120,
)

