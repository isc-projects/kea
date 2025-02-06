if not gtest.found()
    subdir_done()
endif

HOOK_INCLUDES = [include_directories('..')]
dhcp_pgsql_libload_tests = executable(
    'dhcp-pgsql-libload-tests',
    'load_unload_unittests.cc',
    'run_unittests.cc',
    cpp_args: [
        f'-DLIBDHCP_PGSQL_SO="@TOP_BUILD_DIR@/src/hooks/dhcp/pgsql/libdhcp_pgsql.so"',
    ],
    dependencies: [gtest, crypto],
    include_directories: [include_directories('.')] + INCLUDES + HOOK_INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
)
test('dhcp_pgsql_libload_tests', dhcp_pgsql_libload_tests, protocol: 'gtest')
