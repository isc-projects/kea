if not TESTS_OPT.enabled() or not MYSQL_DEP.found()
    subdir_done()
endif

libs_testutils = [
    kea_mysql_testutils_lib,
    kea_database_testutils_lib,
    kea_testutils_lib,
]
kea_mysql_tests = executable(
    'kea-mysql-tests',
    'mysql_binding_unittest.cc',
    'mysql_connection_unittest.cc',
    'run_unittests.cc',
    cpp_args: [f'-DTEST_CA_DIR="@TEST_CA_DIR@"', f'-DKEA_ADMIN="@KEA_ADMIN@"'],
    dependencies: [GTEST_DEP, MYSQL_DEP],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: [kea_util_unittests_lib, libs_testutils] + LIBS_BUILT_SO_FAR,
)
test(
    'kea-mysql-tests',
    kea_mysql_tests,
    protocol: 'gtest',
    is_parallel: false,
    priority: -1,
    timeout: 60,
)
