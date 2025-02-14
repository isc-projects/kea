if not gtest.found()
    subdir_done()
endif

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
    dependencies: [gtest],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
)
test('perfdhcp-tests', perfdhcp_tests, protocol: 'gtest')
