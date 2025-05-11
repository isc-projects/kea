if not TESTS_OPT.enabled()
    subdir_done()
endif

current_build_dir = meson.current_build_dir()
dhcp_lease_query_libloadtests = executable(
    'dhcp-lease-query-libload-tests',
    'load_unload_unittests.cc',
    'run_unittests.cc',
    cpp_args: [
        f'-DTEST_DATA_BUILDDIR="@current_build_dir@"',
        f'-DLIBDHCP_LEASE_QUERY_SO="@TOP_BUILD_DIR@/src/hooks/dhcp/lease_query/libdhcp_lease_query.so"',
    ],
    dependencies: [GTEST_DEP, CRYPTO_DEP],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
)
test(
    'dhcp-lease-query-libloadtests',
    dhcp_lease_query_libloadtests,
    depends: [dhcp_lease_query_lib],
    protocol: 'gtest',
)
