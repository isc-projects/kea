if not gtest.found()
    subdir_done()
endif

current_build_dir = meson.current_build_dir()
kea_d2_tests_data = configuration_data()
kea_d2_tests_data.set('abs_top_builddir', TOP_BUILD_DIR)
kea_d2_tests_data.set('abs_top_srcdir', TOP_SOURCE_DIR)
kea_d2_tests_data.set('abs_builddir', current_build_dir)
d2_process_tests = configure_file(
    input: 'd2_process_tests.sh.in',
    output: 'd2_process_tests.sh',
    configuration: kea_d2_tests_data,
)
test(
    'd2_process_tests.sh',
    d2_process_tests,
    workdir: current_build_dir,
    is_parallel: false,
    priority: -1,
)
configure_file(
    input: 'meson-test_callout_libraries.h.in',
    output: 'test_callout_libraries.h',
    configuration: kea_d2_tests_data,
)
configure_file(
    input: 'test_data_files_config.h.in',
    output: 'test_data_files_config.h',
    configuration: kea_d2_tests_data,
)
configure_file(
    input: 'meson-test_configured_libraries.h.in',
    output: 'test_configured_libraries.h',
    configuration: kea_d2_tests_data,
)

current_source_dir = meson.current_source_dir()
kea_d2_tests_libs = [
    kea_d2srv_testutils_lib,
    kea_process_testutils_lib,
    kea_testutils_lib,
    kea_asiolink_testutils_lib,
]
kea_d2_tests = executable(
    'kea-d2-tests',
    'check_exists_add_unittests.cc',
    'check_exists_remove_unittests.cc',
    'd2_cfg_mgr_unittests.cc',
    'd2_command_unittest.cc',
    'd2_controller_unittests.cc',
    'd2_http_command_unittest.cc',
    'd2_process_unittests.cc',
    'd2_queue_mgr_unittests.cc',
    'd2_simple_parser_unittest.cc',
    'd2_unittests.cc',
    'd2_update_mgr_unittests.cc',
    'get_config_unittest.cc',
    'nc_add_unittests.cc',
    'nc_remove_unittests.cc',
    'parser_unittest.cc',
    'simple_add_unittests.cc',
    'simple_add_without_dhcid_unittests.cc',
    'simple_remove_unittests.cc',
    'simple_remove_without_dhcid_unittests.cc',
    cpp_args: [
        f'-DTEST_DATA_BUILDDIR="@current_build_dir@"',
        f'-DCFG_EXAMPLES="@TOP_SOURCE_DIR@/doc/examples/ddns"',
        f'-DSYNTAX_FILE="@current_source_dir@/../d2_parser.yy"',
        f'-DTEST_CA_DIR="@TEST_CA_DIR@"',
    ],
    dependencies: [gtest],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: [d2_lib] + kea_d2_tests_libs + LIBS_BUILT_SO_FAR,
)
test('kea-d2-tests', kea_d2_tests, protocol: 'gtest')

shared_library(
    'callout',
    'callout_library.cc',
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
    build_rpath: '/nowhere',
    name_suffix: 'so',
)
shared_library(
    'configured',
    'configured_library.cc',
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
    build_rpath: '/nowhere',
    name_suffix: 'so',
)
