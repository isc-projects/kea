if not gtest.found()
    subdir_done()
endif

current_build_dir = meson.current_build_dir()
current_source_dir = meson.current_source_dir()
dhcp6_tests_deps = [crypto, gtest]
dhcp6_tests_libs = [
    kea_dhcpsrv_testutils_lib,
    kea_dhcp_testutils_lib,
    kea_database_testutils_lib,
    kea_testutils_lib,
    kea_util_unittests_lib,
    kea_asiolink_testutils_lib,
]
if mysql.found()
    dhcp6_tests_deps += [mysql]
    dhcp6_tests_libs += [
        dhcp_mysql_archive,
        kea_mysql_testutils_lib,
        kea_mysql_lib,
    ]
endif
if postgresql.found()
    dhcp6_tests_deps += [postgresql]
    dhcp6_tests_libs += [
        dhcp_pgsql_archive,
        kea_pgsql_testutils_lib,
        kea_pgsql_lib,
    ]
endif

dhcp6_tests_conf_data = configuration_data()
dhcp6_tests_conf_data.set('abs_top_builddir', TOP_BUILD_DIR)
dhcp6_tests_conf_data.set('abs_top_srcdir', TOP_SOURCE_DIR)
dhcp6_tests_conf_data.set('abs_builddir', current_build_dir)
dhcp6_tests_conf_data.set('dotlibs', '')
dhcp6_process_tests = configure_file(
    input: 'dhcp6_process_tests.sh.in',
    output: 'dhcp6_process_tests.sh',
    configuration: dhcp6_tests_conf_data,
)
test(
    'dhcp6_process_tests.sh',
    dhcp6_process_tests,
    workdir: current_build_dir,
    is_parallel: false,
    priority: -1,
)
configure_file(
    input: 'marker_file.h.in',
    output: 'marker_file.h',
    configuration: dhcp6_tests_conf_data,
)
configure_file(
    input: 'test_data_files_config.h.in',
    output: 'test_data_files_config.h',
    configuration: dhcp6_tests_conf_data,
)
configure_file(
    input: 'test_libraries.h.in',
    output: 'test_libraries.h',
    configuration: dhcp6_tests_conf_data,
)
kea_dhcp6_tests = executable(
    'kea-dhcp6-tests',
    'classify_unittest.cc',
    'client_handler_unittest.cc',
    'config_backend_unittest.cc',
    'config_parser_unittest.cc',
    'confirm_unittest.cc',
    'ctrl_dhcp6_srv_unittest.cc',
    'd2_unittest.cc',
    'decline_unittest.cc',
    'dhcp6_client.cc',
    'dhcp6_message_test.cc',
    'dhcp6_srv_unittest.cc',
    'dhcp6_test_utils.cc',
    'dhcp6_unittests.cc',
    'dhcp6to4_ipc_unittest.cc',
    'fqdn_unittest.cc',
    'get_config_unittest.cc',
    'hooks_unittest.cc',
    'host_unittest.cc',
    'http_control_socket_unittest.cc',
    'infrequest_unittest.cc',
    'kea_controller_unittest.cc',
    'marker_file.cc',
    'parser_unittest.cc',
    'rebind_unittest.cc',
    'renew_unittest.cc',
    'sarr_unittest.cc',
    'shared_network_unittest.cc',
    'simple_parser6_unittest.cc',
    'tee_times_unittest.cc',
    'vendor_opts_unittest.cc',
    cpp_args: [
        f'-DTOP_BUILDDIR="@TOP_BUILD_DIR@"',
        f'-DTEST_DATA_BUILDDIR="@current_build_dir@"',
        f'-DCFG_EXAMPLES="@TOP_SOURCE_DIR@/doc/examples/kea6"',
        f'-DDHCP_DATA_DIR="@current_build_dir@"',
        f'-DSYNTAX_FILE="@current_source_dir@/../dhcp6_parser.yy"',
        f'-DKEA_LFC_EXECUTABLE="@KEA_LFC@"',
        f'-DTEST_CA_DIR="@TEST_CA_DIR@"',
    ],
    dependencies: dhcp6_tests_deps,
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: [dhcp6_lib] + dhcp6_tests_libs + LIBS_BUILT_SO_FAR,
)
test(
    'kea-dhcp6-tests',
    kea_dhcp6_tests,
    protocol: 'gtest',
    is_parallel: false,
    priority: -1,
)

shared_library(
    'co1',
    'callout_library_1.cc',
    dependencies: dhcp6_tests_deps,
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
    build_rpath: '/nowhere',
    name_suffix: 'so',
)
shared_library(
    'co2',
    'callout_library_2.cc',
    dependencies: dhcp6_tests_deps,
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
    build_rpath: '/nowhere',
    name_suffix: 'so',
)
shared_library(
    'co3',
    'callout_library_3.cc',
    dependencies: dhcp6_tests_deps,
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
    build_rpath: '/nowhere',
    name_suffix: 'so',
)
shared_library(
    'co4',
    'callout_library_4.cc',
    dependencies: dhcp6_tests_deps,
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
    build_rpath: '/nowhere',
    name_suffix: 'so',
)
