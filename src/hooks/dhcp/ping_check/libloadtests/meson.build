if not gtest.found()
    subdir_done()
endif

dhcp_ping_check_libloadtests = executable(
    'dhcp-ping-check-libload-tests',
    'load_unload_unittests.cc',
    'run_unittests.cc',
    cpp_args: [
        f'-DPING_CHECK_LIB_SO="@TOP_BUILD_DIR@/src/hooks/dhcp/ping_check/libdhcp_ping_check.so"',
    ],
    dependencies: [gtest, crypto],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
)
test(
    'dhcp-ping-check-libloadtests',
    dhcp_ping_check_libloadtests,
    depends: [dhcp_ping_check_lib],
    protocol: 'gtest',
)
