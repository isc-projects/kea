if not gtest.found()
    subdir_done()
endif

kea_testutils_lib = static_library(
    'kea-testutils',
    'io_utils.cc',
    'log_utils.cc',
    'test_to_element.cc',
    'threaded_test.cc',
    'unix_control_client.cc',
    'user_context_utils.cc',
    dependencies: [gtest],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: [kea_util_unittests_lib] + LIBS_BUILT_SO_FAR,
)

dhcp_test_lib_conf_data = configuration_data()
dhcp_test_lib_conf_data.set('abs_top_builddir', TOP_BUILD_DIR)
dhcp_test_lib_conf_data.set('prefix', PREFIX)
dhcp_test_lib_conf_data.set('PACKAGE_VERSION', project_version)
configure_file(
    input: 'dhcp_test_lib.sh.in',
    output: 'dhcp_test_lib.sh',
    configuration: dhcp_test_lib_conf_data,
)
configure_file(
    input: 'xml_reporting_test_lib.sh.in',
    output: 'xml_reporting_test_lib.sh',
    copy: true,
)
