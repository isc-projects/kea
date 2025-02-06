if not gtest.found()
    subdir_done()
endif

HOOK_INCLUDES = [include_directories('..')]
dhcp_stat_cmds_lib_tests = executable(
    'dhcp-stat-cmds-lib-tests',
    'run_unittests.cc',
    'stat_cmds_unittest.cc',
    cpp_args: [
        f'-DSTAT_CMDS_LIB_SO="@TOP_BUILD_DIR@/src/hooks/dhcp/stat_cmds/libdhcp_stat_cmds.so"',
    ],
    dependencies: [gtest, crypto],
    include_directories: [include_directories('.')] + INCLUDES + HOOK_INCLUDES,
    link_with: [dhcp_stat_cmds_archive] + LIBS_BUILT_SO_FAR,
)
test('dhcp_stat_cmds_lib_tests', dhcp_stat_cmds_lib_tests, protocol: 'gtest')
