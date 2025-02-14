if not gtest.found()
    subdir_done()
endif

dhcp_stat_cmds_libload_tests = executable(
    'dhcp-stat-cmds-libload-tests',
    'load_unload_unittests.cc',
    'run_unittests.cc',
    cpp_args: [
        f'-DLIBDHCP_STAT_CMDS_SO="@TOP_BUILD_DIR@/src/hooks/dhcp/stat_cmds/libdhcp_stat_cmds.so"',
    ],
    dependencies: [gtest, crypto],
    include_directories: [include_directories('.'), include_directories('..')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
)
test(
    'dhcp-stat-cmds-libload-tests',
    dhcp_stat_cmds_libload_tests,
    protocol: 'gtest',
)
