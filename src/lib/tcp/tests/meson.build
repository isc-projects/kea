if not gtest.found()
    subdir_done()
endif

kea_tcp_tests = executable(
    'kea-tcp-tests',
    'mt_tcp_listener_mgr_unittests.cc',
    'run_unittests.cc',
    'tcp_listener_unittests.cc',
    cpp_args: [f'-DTEST_CA_DIR="@TEST_CA_DIR@"'],
    dependencies: [gtest, crypto],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: [kea_util_unittests_lib, kea_asiolink_testutils_lib] + LIBS_BUILT_SO_FAR,
)
test('kea_tcp_tests', kea_tcp_tests, protocol: 'gtest', is_parallel: false)
