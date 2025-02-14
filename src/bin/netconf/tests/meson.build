if not gtest.found() or not NETCONF_DEPS_FOUND
    subdir_done()
endif

kea_netconf_tests = executable(
    'kea-netconf-tests',
    'basic_library.cc',
    'control_socket_unittests.cc',
    'get_config_unittest.cc',
    'netconf_cfg_mgr_unittests.cc',
    'netconf_controller_unittests.cc',
    'netconf_process_unittests.cc',
    'netconf_unittests.cc',
    'parser_unittests.cc',
    'run_unittests.cc',
    dependencies: NETCONF_DEPS_ARRAY + [gtest],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: [kea_yang_tests_lib] + LIBS_BUILT_SO_FAR,
    override_options: ['cpp_std=c++20'],
)
test('kea-netconf-tests', kea_netconf_tests, protocol: 'gtest')
