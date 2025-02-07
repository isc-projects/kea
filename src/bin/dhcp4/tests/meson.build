if not gtest.found()
    subdir_done()
endif

CURRENT_BUILD_DIR = meson.current_build_dir()
CURRENT_SOURCE_DIR = meson.current_source_dir()
libs_testutils = [
    kea_dhcpsrv_testutils_lib,
    kea_dhcp_testutils_lib,
    kea_database_testutils_lib,
    kea_testutils_lib,
]
dhcp4_tests_conf_data = configuration_data()
dhcp4_tests_conf_data.set('abs_top_builddir', TOP_BUILD_DIR)
dhcp4_tests_conf_data.set('abs_top_srcdir', TOP_SOURCE_DIR)
dhcp4_tests_conf_data.set('abs_builddir', meson.current_build_dir())
dhcp4_process_tests = configure_file(
    input: 'meson-dhcp4_process_tests.sh.in',
    output: 'dhcp4_process_tests.sh',
    configuration: dhcp4_tests_conf_data,
)
test(
    'dhcp4_process_tests.sh',
    dhcp4_process_tests,
    workdir: CURRENT_BUILD_DIR,
    is_parallel: false,
)
configure_file(
    input: 'marker_file.h.in',
    output: 'marker_file.h',
    configuration: dhcp4_tests_conf_data,
)
configure_file(
    input: 'test_data_files_config.h.in',
    output: 'test_data_files_config.h',
    configuration: dhcp4_tests_conf_data,
)
configure_file(
    input: 'meson-test_libraries.h.in',
    output: 'test_libraries.h',
    configuration: dhcp4_tests_conf_data,
)
# Not yet used configs-list.txt
dhcp4_unittests = executable(
    'dhcp4_unittests',
    'classify_unittest.cc',
    'client_handler_unittest.cc',
    'config_parser_unittest.cc',
    'config_backend_unittest.cc',
    'ctrl_dhcp4_srv_unittest.cc',
    'http_control_socket_unittest.cc',
    'd2_unittest.cc',
    'decline_unittest.cc',
    'dhcp4_client.cc',
    'dhcp4_srv_unittest.cc',
    'dhcp4_test_utils.cc',
    'dhcp4_unittests.cc',
    'dhcp4to6_ipc_unittest.cc',
    'direct_client_unittest.cc',
    'dora_unittest.cc',
    'fqdn_unittest.cc',
    'get_config_unittest.cc',
    'hooks_unittest.cc',
    'host_options_unittest.cc',
    cpp_args: [
        f'-DTEST_DATA_BUILDDIR="@CURRENT_BUILD_DIR@"',
        f'-DCFG_EXAMPLES="@TOP_SOURCE_DIR@/doc/examples/kea4"',
        f'-DDHCP_DATA_DIR="@CURRENT_BUILD_DIR@"',
        f'-DSYNTAX_FILE="@CURRENT_SOURCE_DIR@/../dhcp4_parser.yy"',
        f'-DKEA_LFC_EXECUTABLE="@KEA_LFC@"',
        f'-DTEST_CA_DIR="@TEST_CA_DIR@"',
    ],
    dependencies: [boost, crypto, gtest],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: [kea_util_unittests_lib] + libs_testutils + LIBS_BUILT_SO_FAR,
)
test('dhcp4_unittests', dhcp4_unittests, protocol: 'gtest', is_parallel: false)

shared_library(
    'co1',
    'callout_library_1.cc',
    dependencies: [boost],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
    build_rpath: '/nowhere',
    name_suffix: 'so',
)
shared_library(
    'co2',
    'callout_library_2.cc',
    dependencies: [boost],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
    build_rpath: '/nowhere',
    name_suffix: 'so',
)
shared_library(
    'co3',
    'callout_library_3.cc',
    dependencies: [boost],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
    build_rpath: '/nowhere',
    name_suffix: 'so',
)
shared_library(
    'co4',
    'callout_library_4.cc',
    dependencies: [boost],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
    build_rpath: '/nowhere',
    name_suffix: 'so',
)
