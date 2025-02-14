if not gtest.found()
    subdir_done()
endif

current_build_dir = meson.current_build_dir()

kea_agent_tests = executable(
    'kea-agent-tests',
    'basic_auth_library.cc',
    'ca_cfg_mgr_unittests.cc',
    'ca_command_mgr_unittests.cc',
    'ca_controller_unittests.cc',
    'ca_process_unittests.cc',
    'ca_response_creator_factory_unittests.cc',
    'ca_response_creator_unittests.cc',
    'ca_unittests.cc',
    'callout_library.cc',
    'get_config_unittest.cc',
    'parser_unittests.cc',
    cpp_args: [
        f'-DCFG_EXAMPLES="@TOP_SOURCE_DIR@/doc/examples/agent"',
        f'-DSYNTAX_FILE="@current_source_dir@/../agent_parser.yy"',
        f'-DTEST_CA_DIR="@TEST_CA_DIR@"',
        f'-DTEST_DATA_BUILDDIR="@current_build_dir@"',
    ],
    dependencies: [gtest],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: [agent_lib] + LIBS_BUILT_SO_FAR,
)
test('kea-agent-tests', kea_agent_tests, protocol: 'gtest')
