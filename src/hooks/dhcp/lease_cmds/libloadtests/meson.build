if not gtest.found()
    subdir_done()
endif

dhcp_lease_cmds_libload_tests = executable(
    'dhcp-lease-cmds-libload-tests',
    'load_unload_unittests.cc',
    'run_unittests.cc',
    cpp_args: [
        f'-DLIBDHCP_LEASE_CMDS_SO="@TOP_BUILD_DIR@/src/hooks/dhcp/lease_cmds/libdhcp_lease_cmds.so"',
    ],
    dependencies: [gtest, crypto],
    include_directories: [include_directories('.'), include_directories('..')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
)
test(
    'dhcp_lease_cmds_libload_tests',
    dhcp_lease_cmds_libload_tests,
    protocol: 'gtest',
)
