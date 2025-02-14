if not gtest.found()
    subdir_done()
endif

current_build_dir = meson.current_build_dir()
kea_agent_tests_data = configuration_data()
kea_agent_tests_data.set('abs_top_builddir', TOP_BUILD_DIR)
kea_agent_tests_data.set('abs_top_srcdir', TOP_SOURCE_DIR)
kea_agent_tests_data.set('abs_builddir', current_build_dir)
ca_process_tests = configure_file(
    input: 'ca_process_tests.sh.in',
    output: 'ca_process_tests.sh',
    configuration: kea_agent_tests_data,
)
test(
    'ca_process_tests.sh',
    ca_process_tests,
    workdir: current_build_dir,
    is_parallel: false,
    priority: -1,
)
configure_file(
    input: 'meson-test_basic_auth_libraries.h.in',
    output: 'test_basic_auth_libraries.h',
    configuration: kea_agent_tests_data,
)
configure_file(
    input: 'meson-test_callout_libraries.h.in',
    output: 'test_callout_libraries.h',
    configuration: kea_agent_tests_data,
)
configure_file(
    input: 'test_data_files_config.h.in',
    output: 'test_data_files_config.h',
    configuration: kea_agent_tests_data,
)

current_source_dir = meson.current_source_dir()
kea_agent_tests_libs = [
    kea_process_testutils_lib,
    kea_testutils_lib,
    kea_asiolink_testutils_lib,
]
kea_agent_tests = executable(
    'kea-agent-tests',
    'ca_cfg_mgr_unittests.cc',
    'ca_command_mgr_unittests.cc',
    'ca_controller_unittests.cc',
    'ca_process_unittests.cc',
    'ca_response_creator_factory_unittests.cc',
    'ca_response_creator_unittests.cc',
    'ca_unittests.cc',
    'get_config_unittest.cc',
    'parser_unittests.cc',
    cpp_args: [
        f'-DTEST_DATA_BUILDDIR="@current_build_dir@"',
        f'-DCFG_EXAMPLES="@TOP_SOURCE_DIR@/doc/examples/agent"',
        f'-DSYNTAX_FILE="@current_source_dir@/../agent_parser.yy"',
        f'-DTEST_CA_DIR="@TEST_CA_DIR@"',
    ],
    dependencies: [gtest, crypto],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: [agent_lib] + kea_agent_tests_libs + LIBS_BUILT_SO_FAR,
)
test('kea-agent-tests', kea_agent_tests, protocol: 'gtest')

shared_library(
    'callout',
    'callout_library.cc',
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
    build_rpath: '/nowhere',
    name_suffix: 'so',
)
shared_library(
    'basicauth',
    'basic_auth_library.cc',
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
    build_rpath: '/nowhere',
    name_suffix: 'so',
)
