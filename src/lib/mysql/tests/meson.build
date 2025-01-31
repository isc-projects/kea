LIBS_TESTUTILS = [
    kea_mysql_testutils_lib,
    kea_database_testutils_lib,
    kea_testutils_lib
]
kea_mysql_tests = executable(
    'kea-mysql-tests',
    'mysql_binding_unittest.cc',
    'mysql_connection_unittest.cc',
    'run_unittests.cc',
    cpp_args: [f'-DTEST_CA_DIR="@TEST_CA_DIR@"',
               f'-DKEA_ADMIN="@KEA_ADMIN@"'],
    dependencies: [gtest, mysql],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR + LIBS_TESTUTILS + [kea_util_unittests_lib],
)
test('kea_mysql_tests', kea_mysql_tests, protocol: 'gtest')
