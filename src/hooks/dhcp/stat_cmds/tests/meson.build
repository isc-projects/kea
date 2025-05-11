if not TESTS_OPT.enabled()
    subdir_done()
endif

dhcp_stat_cmds_lib_tests = executable(
    'dhcp-stat-cmds-lib-tests',
    'run_unittests.cc',
    'stat_cmds_unittest.cc',
    cpp_args: [
        f'-DSTAT_CMDS_LIB_SO="@TOP_BUILD_DIR@/src/hooks/dhcp/stat_cmds/libdhcp_stat_cmds.so"',
    ],
    dependencies: [GTEST_DEP, CRYPTO_DEP],
    include_directories: [include_directories('.'), include_directories('..')] + INCLUDES,
    link_with: [dhcp_stat_cmds_archive] + LIBS_BUILT_SO_FAR,
)
test('dhcp-stat-cmds-lib-tests', dhcp_stat_cmds_lib_tests, protocol: 'gtest')
