if not TESTS_OPT.enabled()
    subdir_done()
endif

current_build_dir = meson.current_build_dir()
dhcp_lease_query_tests_dependencies = [GTEST_DEP, CRYPTO_DEP]
dhcp_lease_query_tests_libs = [dhcp_lease_query_archive]
if MYSQL_DEP.found()
    dhcp_lease_query_tests_libs += [dhcp_mysql_archive, kea_mysql_testutils_lib]
    dhcp_lease_query_tests_dependencies += [MYSQL_DEP]
endif
if POSTGRESQL_DEP.found()
    dhcp_lease_query_tests_libs += [dhcp_pgsql_archive, kea_pgsql_testutils_lib]
    dhcp_lease_query_tests_dependencies += [POSTGRESQL_DEP]
endif
dhcp_lease_query_tests_libs += [
    kea_dhcp_testutils_lib,
    kea_database_testutils_lib,
    kea_testutils_lib,
    kea_asiolink_testutils_lib,
]

dhcp_lease_query_tests = executable(
    'dhcp-lease-query-tests',
    'accept_filter4_unittest.cc',
    'accept_filter6_unittest.cc',
    'bulk_lease_query4_unittest.cc',
    'bulk_lease_query6_unittest.cc',
    'lease_query4_unittest.cc',
    'lease_query6_unittest.cc',
    'lease_query_connection_unittest.cc',
    'lease_query_impl4_unittest.cc',
    'lease_query_impl6_unittest.cc',
    'lease_query_listener4_unittest.cc',
    'lease_query_listener6_unittest.cc',
    'mt_lease_query_mgr4_unittest.cc',
    'mt_lease_query_mgr6_unittest.cc',
    'run_unittests.cc',
    cpp_args: [f'-DTEST_DATA_BUILDDIR="@current_build_dir@"'],
    dependencies: dhcp_lease_query_tests_dependencies,
    include_directories: [include_directories('.'), include_directories('..')] + INCLUDES,
    link_with: [dhcp_lease_query_tests_libs] + LIBS_BUILT_SO_FAR,
)
test(
    'dhcp-lease-query-tests',
    dhcp_lease_query_tests,
    protocol: 'gtest',
    is_parallel: false,
    priority: -1,
)
