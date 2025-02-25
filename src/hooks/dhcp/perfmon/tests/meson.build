if not gtest.found()
    subdir_done()
endif

dhcp_perfmon_lib_tests = executable(
    'dhcp-perfmon-lib-tests',
    'alarm_parser_unittests.cc',
    'alarm_unittests.cc',
    'duration_key_parser_unittests.cc',
    'monitored_duration_unittests.cc',
    'perfmon_cmds_unittests.cc',
    'perfmon_config_unittests.cc',
    'perfmon_mgr_unittests.cc',
    'run_unittests.cc',
    cpp_args: [
        f'-DPERFMON_LIB_SO="@TOP_BUILD_DIR@/src/hooks/dhcp/perfmon/libdhcp_perfmon.so"',
    ],
    dependencies: [gtest, crypto],
    include_directories: [include_directories('.'), include_directories('..')] + INCLUDES,
    link_with: [dhcp_perfmon_archive, [kea_testutils_lib]] + LIBS_BUILT_SO_FAR,
)
test(
    'dhcp-perfmon-lib-tests',
    dhcp_perfmon_lib_tests,
    protocol: 'gtest',
    is_parallel: false,
    priority: -1,
)
