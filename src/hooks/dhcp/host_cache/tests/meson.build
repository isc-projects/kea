if not TESTS_OPT.enabled()
    subdir_done()
endif

current_build_dir = meson.current_build_dir()
dhcp_host_cache_tests_libs = [
    dhcp_host_cache_archive,
    kea_dhcpsrv_testutils_lib,
    kea_database_testutils_lib,
    kea_testutils_lib,
]
dhcp_host_cache_tests = executable(
    'dhcp-host-cache-tests',
    'cache_unittests.cc',
    'command_unittests.cc',
    'host_data_source_unittests.cc',
    'run_unittests.cc',
    cpp_args: [f'-DTEST_DATA_BUILDDIR="@current_build_dir@"'],
    dependencies: [GTEST_DEP, CRYPTO_DEP],
    include_directories: [include_directories('.'), include_directories('..')] + INCLUDES,
    link_with: [dhcp_host_cache_tests_libs] + LIBS_BUILT_SO_FAR,
)
test(
    'dhcp-host-cache-tests',
    dhcp_host_cache_tests,
    is_parallel: false,
    priority: -1,
    protocol: 'gtest',
)
