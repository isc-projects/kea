if not gtest.found()
    subdir_done()
endif

dhcp_mysql_libload_tests = executable(
    'dhcp-mysql-libload-tests',
    'load_unload_unittests.cc',
    'run_unittests.cc',
    cpp_args: [
        f'-DLIBDHCP_MYSQL_SO="@TOP_BUILD_DIR@/src/hooks/dhcp/mysql/libdhcp_mysql.so"',
    ],
    dependencies: [gtest, crypto],
    include_directories: [include_directories('.'), include_directories('..')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
)
test('dhcp-mysql-libload-tests', dhcp_mysql_libload_tests, protocol: 'gtest')
