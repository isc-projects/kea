if not TESTS_OPT.enabled() or not POSTGRESQL_DEP.found()
    subdir_done()
endif

libs_testutils = [
    kea_pgsql_testutils_lib,
    kea_database_testutils_lib,
    kea_testutils_lib,
]
kea_pgsql_tests = executable(
    'kea-pgsql-tests',
    'pgsql_basics.cc',
    'pgsql_connection_unittest.cc',
    'pgsql_exchange_unittest.cc',
    'run_unittests.cc',
    cpp_args: [
        f'-DTEST_CA_DIR="@TEST_CA_DIR@"',
        f'-DKEA_ADMIN="@KEA_ADMIN_BUILT@"',
    ],
    dependencies: [GTEST_DEP, POSTGRESQL_DEP],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: [kea_util_unittests_lib, libs_testutils] + LIBS_BUILT_SO_FAR,
)
test(
    'kea-pgsql-tests',
    kea_pgsql_tests,
    protocol: 'gtest',
    is_parallel: false,
    priority: -1,
    timeout: 120,
)
