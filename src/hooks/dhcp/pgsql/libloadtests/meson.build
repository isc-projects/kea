if not gtest.found()
    subdir_done()
endif

dhcp_pgsql_libload_tests = executable(
    'dhcp-pgsql-libload-tests',
    'load_unload_unittests.cc',
    'run_unittests.cc',
    cpp_args: [
        f'-DLIBDHCP_PGSQL_SO="@TOP_BUILD_DIR@/src/hooks/dhcp/pgsql/libdhcp_pgsql.so"',
    ],
    dependencies: [gtest, crypto],
    include_directories: [include_directories('.'), include_directories('..')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
)
test(
    'dhcp-pgsql-libload-tests',
    dhcp_pgsql_libload_tests,
    depends: [dhcp_pgsql_lib],
    protocol: 'gtest',
)
