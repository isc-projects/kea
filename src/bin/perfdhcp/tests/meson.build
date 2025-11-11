if not TESTS_OPT.enabled()
    subdir_done()
endif

current_source_dir = meson.current_source_dir()
perfdhcp_tests = executable(
    'perfdhcp-tests',
    'avalanche_scen_unittest.cc',
    'basic_scen_unittest.cc',
    'command_options_unittest.cc',
    'localized_option_unittest.cc',
    'packet_storage_unittest.cc',
    'perf_pkt4_unittest.cc',
    'perf_pkt6_unittest.cc',
    'perf_socket_unittest.cc',
    'rate_control_unittest.cc',
    'receiver_unittest.cc',
    'run_unittests.cc',
    'stats_mgr_unittest.cc',
    'test_control_unittest.cc',
    cpp_args: [f'-DTEST_DATA_DIR="@current_source_dir@/testdata"'],
    dependencies: [GTEST_DEP],
    include_directories: [include_directories('.'), include_directories('..')] + INCLUDES,
    link_with: [perfdhcp_lib, kea_util_unittests_lib] + LIBS_BUILT_SO_FAR,
)
test(
    'perfdhcp-tests',
    perfdhcp_tests,
    protocol: 'gtest',
    is_parallel: false,
    priority: -1,
)

perfdhcp_tests_conf_data = configuration_data()
perfdhcp_tests_conf_data.set('abs_top_builddir', TOP_BUILD_DIR)
perfdhcp_process_tests = configure_file(
    input: 'perfdhcp_process_tests.sh.in',
    output: 'perfdhcp_process_tests.sh',
    configuration: perfdhcp_tests_conf_data,
)
test(
    'perfdhcp_process_tests.sh',
    perfdhcp_process_tests,
    workdir: current_build_dir,
    is_parallel: false,
    priority: -1,
    suite: 'shell-tests',
)
