if not TESTS_OPT.enabled()
    subdir_done()
endif

dhcp_ha_lib_tests = executable(
    'dhcp-ha-lib-tests',
    'command_creator_unittest.cc',
    'communication_state_unittest.cc',
    'ha_config_unittest.cc',
    'ha_impl_unittest.cc',
    'ha_mt_unittest.cc',
    'ha_relationship_mapper_unittest.cc',
    'ha_service_unittest.cc',
    'ha_test.cc',
    'lease_sync_filter_unittest.cc',
    'lease_update_backlog_unittest.cc',
    'query_filter_unittest.cc',
    'run_unittests.cc',
    cpp_args: [
        f'-DLIBDHCP_HA_SO="@TOP_BUILD_DIR@/src/hooks/dhcp/high_availability/libdhcp_ha.so"',
        f'-DTEST_CA_DIR="@TEST_CA_DIR@"',
        f'-DTEST_HTTP_DIR="@TOP_SOURCE_DIR@/src/lib/http/tests/testdata"',
    ],
    dependencies: [GTEST_DEP, CRYPTO_DEP],
    include_directories: [include_directories('.'), include_directories('..')] + INCLUDES,
    link_with: [dhcp_ha_archive, [kea_testutils_lib]] + LIBS_BUILT_SO_FAR,
)
test(
    'dhcp-ha-lib-tests',
    dhcp_ha_lib_tests,
    protocol: 'gtest',
    is_parallel: false,
    priority: -1,
    timeout: 60,
)
