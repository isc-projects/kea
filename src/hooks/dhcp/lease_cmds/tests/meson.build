if not gtest.found()
    subdir_done()
endif

dhcp_lease_cmds_lib_tests = executable(
    'dhcp-lease-cmds-lib-tests',
    'lease_cmds4_unittest.cc',
    'lease_cmds6_unittest.cc',
    'lease_cmds_unittest.cc',
    'run_unittests.cc',
    cpp_args: [
        f'-DLEASE_CMDS_LIB_SO="@TOP_BUILD_DIR@/src/hooks/dhcp/lease_cmds/libdhcp_lease_cmds.so"',
    ],
    dependencies: [gtest, crypto],
    include_directories: [include_directories('.'), include_directories('..')] + INCLUDES,
    link_with: [dhcp_lease_cmds_archive] + LIBS_BUILT_SO_FAR,
)
test('dhcp-lease-cmds-lib-tests', dhcp_lease_cmds_lib_tests, protocol: 'gtest')
