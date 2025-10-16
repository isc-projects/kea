if not TESTS_OPT.enabled()
    subdir_done()
endif

dhcp_ping_check_libloadtests = executable(
    'dhcp-ping-check-libload-tests',
    'callout_unittests.cc',
    'load_unload_unittests.cc',
    'run_unittests.cc',
    cpp_args: [
        f'-DPING_CHECK_LIB_SO="@TOP_BUILD_DIR@/src/hooks/dhcp/ping_check/libdhcp_ping_check.so"',
    ],
    dependencies: [GTEST_DEP, CRYPTO_DEP],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: [kea_testutils_lib] + LIBS_BUILT_SO_FAR,
)
test(
    'dhcp-ping-check-libloadtests',
    dhcp_ping_check_libloadtests,
    depends: [dhcp_ping_check_lib],
    protocol: 'gtest',
)
