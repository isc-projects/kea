if not TESTS_OPT.enabled()
    subdir_done()
endif

current_build_dir = meson.current_build_dir()
current_source_dir = meson.current_source_dir()
dhcp4_tests_deps = [CRYPTO_DEP, GTEST_DEP]
dhcp4_tests_libs = [
    kea_dhcpsrv_testutils_lib,
    kea_dhcp_testutils_lib,
    kea_database_testutils_lib,
    kea_testutils_lib,
    kea_util_unittests_lib,
    kea_asiolink_testutils_lib,
]
if MYSQL_DEP.found()
    dhcp4_tests_deps += [MYSQL_DEP]
    dhcp4_tests_libs += [
        dhcp_mysql_archive,
        kea_mysql_testutils_lib,
        kea_mysql_lib,
    ]
endif
if POSTGRESQL_DEP.found()
    dhcp4_tests_deps += [POSTGRESQL_DEP]
    dhcp4_tests_libs += [
        dhcp_pgsql_archive,
        kea_pgsql_testutils_lib,
        kea_pgsql_lib,
    ]
endif

dhcp4_tests_conf_data = configuration_data()
dhcp4_tests_conf_data.set('abs_top_builddir', TOP_BUILD_DIR)
dhcp4_tests_conf_data.set('abs_top_srcdir', TOP_SOURCE_DIR)
dhcp4_tests_conf_data.set('abs_builddir', current_build_dir)
dhcp4_tests_conf_data.set('dotlibs', '')
dhcp4_process_tests = configure_file(
    input: 'dhcp4_process_tests.sh.in',
    output: 'dhcp4_process_tests.sh',
    configuration: dhcp4_tests_conf_data,
)
test(
    'dhcp4_process_tests.sh',
    dhcp4_process_tests,
    workdir: current_build_dir,
    is_parallel: false,
    priority: -1,
    suite: 'shell-tests',
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
    input: 'test_libraries.h.in',
    output: 'test_libraries.h',
    configuration: dhcp4_tests_conf_data,
)

co1 = shared_library(
    'co1',
    'callout_library_1.cc',
    dependencies: dhcp4_tests_deps,
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
    build_rpath: '/nowhere',
    name_suffix: 'so',
)
co2 = shared_library(
    'co2',
    'callout_library_2.cc',
    dependencies: dhcp4_tests_deps,
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
    build_rpath: '/nowhere',
    name_suffix: 'so',
)
co3 = shared_library(
    'co3',
    'callout_library_3.cc',
    dependencies: dhcp4_tests_deps,
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
    build_rpath: '/nowhere',
    name_suffix: 'so',
)
co4 = shared_library(
    'co4',
    'callout_library_4.cc',
    dependencies: dhcp4_tests_deps,
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
    build_rpath: '/nowhere',
    name_suffix: 'so',
)

dhcp4_tests_cpp_args = [
    f'-DTEST_DATA_BUILDDIR="@current_build_dir@"',
    f'-DCFG_EXAMPLES="@TOP_SOURCE_DIR@/doc/examples/kea4"',
    f'-DDHCP_DATA_DIR="@SHAREDSTATEDIR_INSTALLED@"',
    f'-DSYNTAX_FILE="@current_source_dir@/../dhcp4_parser.yy"',
    f'-DKEA_LFC_EXECUTABLE="@KEA_LFC_BUILT@"',
    f'-DTEST_CA_DIR="@TEST_CA_DIR@"',
]

# Not yet used configs-list.txt
kea_dhcp4_tests = executable(
    'kea-dhcp4-tests',
    'classify_unittest.cc',
    'client_handler_unittest.cc',
    'config_backend_unittest.cc',
    'config_parser_unittest.cc',
    'ctrl_dhcp4_srv_unittest.cc',
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
    'host_unittest.cc',
    'http_control_socket_unittest.cc',
    'inform_unittest.cc',
    'kea_controller_unittest.cc',
    'marker_file.cc',
    'out_of_range_unittest.cc',
    'parser_unittest.cc',
    'release_unittest.cc',
    'shared_network_unittest.cc',
    'simple_parser4_unittest.cc',
    'vendor_opts_unittest.cc',
    cpp_args: dhcp4_tests_cpp_args,
    dependencies: dhcp4_tests_deps,
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: [dhcp4_lib] + dhcp4_tests_libs + LIBS_BUILT_SO_FAR,
)
test(
    'kea-dhcp4-tests',
    kea_dhcp4_tests,
    # kea_dhcp4 is not really a dependency of this set of tests, but it is used
    # in other tests such as memfile_tests.sh, and since it cannot be specified
    # on the "depends" of a shell test, specify it here instead to have it
    # created on "meson test".
    depends: [co1, co2, co3, co4, kea_dhcp4],
    protocol: 'gtest',
    is_parallel: false,
    priority: -1,
    timeout: 60,
)

get_config_unittest_rebuild = configure_file(
    input: 'get_config_unittest.cc.skel',
    output: 'get_config_unittest_rebuild.cc',
    copy: true,
)
kea_dhcp4_tests_extract = executable(
    'kea-dhcp4-tests-extract',
    get_config_unittest_rebuild,
    'config_parser_unittest.cc',
    objects: kea_dhcp4_tests.extract_objects(
        'dhcp4_test_utils.cc',
        'dhcp4_unittests.cc',
        'marker_file.cc',
    ),
    cpp_args: ['-DEXTRACT_CONFIG'] + dhcp4_tests_cpp_args,
    dependencies: dhcp4_tests_deps,
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: [dhcp4_lib] + dhcp4_tests_libs + LIBS_BUILT_SO_FAR,
    build_by_default: false,
)
kea_dhcp4_tests_generate = executable(
    'kea-dhcp4-tests-generate',
    get_config_unittest_rebuild,
    'config_parser_unittest.cc',
    objects: kea_dhcp4_tests.extract_objects(
        'dhcp4_test_utils.cc',
        'dhcp4_unittests.cc',
        'marker_file.cc',
    ),
    cpp_args: ['-DGENERATE_ACTION'] + dhcp4_tests_cpp_args,
    dependencies: dhcp4_tests_deps,
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: [dhcp4_lib] + dhcp4_tests_libs + LIBS_BUILT_SO_FAR,
    build_by_default: false,
)

make_rebuild_conf = configuration_data()
make_rebuild_conf.set('builddir', current_build_dir)
make_rebuild_conf.set('source', current_source_dir / 'get_config_unittest.cc')
make_rebuild_conf.set(
    'skeleton',
    current_source_dir / 'get_config_unittest.cc.skel',
)
make_rebuild = configure_file(
    input: 'make-rebuild.sh.in',
    output: 'make-rebuild.sh',
    configuration: make_rebuild_conf,
)
# Better when not use as a target.
find_program(make_rebuild, required: true)
