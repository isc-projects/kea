if not gtest.found()
    subdir_done()
endif

current_build_dir = meson.current_build_dir()
libs_testutils = [kea_testutils_lib, kea_asiolink_testutils_lib]
kea_config_tests = executable(
    'kea-config-tests',
    'client_connection_unittests.cc',
    'cmd_http_listener_unittests.cc',
    'cmd_response_creator_factory_unittests.cc',
    'cmd_response_creator_unittests.cc',
    'command_mgr_unittests.cc',
    'http_command_config_unittests.cc',
    'http_command_mgr_unittests.cc',
    'http_command_response_creator_factory_unittests.cc',
    'http_command_response_creator_unittests.cc',
    'run_unittests.cc',
    'unix_command_config_unittests.cc',
    'unix_command_mgr_unittests.cc',
    dependencies: [gtest, crypto],
    cpp_args: [
        f'-DTEST_DATA_BUILDDIR="@current_build_dir@"',
        f'-DTEST_CA_DIR="@TEST_CA_DIR@"',
    ],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: [kea_util_unittests_lib] + libs_testutils + LIBS_BUILT_SO_FAR,
)
test('kea_config_tests', kea_config_tests, protocol: 'gtest')
