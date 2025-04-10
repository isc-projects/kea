if not TESTS_OPT.enabled() or not POSTGRESQL_DEP.found()
    subdir_done()
endif

libs_testutils = [
    kea_dhcpsrv_testutils_lib,
    kea_pgsql_testutils_lib,
    kea_database_testutils_lib,
]
dhcp_pgsql_lib_tests = executable(
    'dhcp-pgsql-lib-tests',
    'pgsql_bootp_unittest.cc',
    'pgsql_cb_dhcp4_mgr_unittest.cc',
    'pgsql_cb_dhcp4_unittest.cc',
    'pgsql_cb_dhcp6_mgr_unittest.cc',
    'pgsql_cb_dhcp6_unittest.cc',
    'pgsql_cb_impl_unittest.cc',
    'pgsql_forensic_unittest.cc',
    'pgsql_host_data_source_unittest.cc',
    'pgsql_lease_extended_info_unittest.cc',
    'pgsql_lease_mgr_unittest.cc',
    'run_unittests.cc',
    dependencies: [GTEST_DEP, CRYPTO_DEP, POSTGRESQL_DEP],
    include_directories: [include_directories('.'), include_directories('..')] + INCLUDES,
    link_with: [dhcp_pgsql_archive, libs_testutils, kea_testutils_lib] + LIBS_BUILT_SO_FAR,
)
test(
    'dhcp-pgsql-lib-tests',
    dhcp_pgsql_lib_tests,
    protocol: 'gtest',
    is_parallel: false,
    priority: -1,
    timeout: 480,
)
