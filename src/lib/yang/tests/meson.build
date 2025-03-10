if not TESTS_OPT.enabled() or not NETCONF_DEP.found()
    subdir_done()
endif

kea_yang_tests_libs = [
    kea_yang_testutils_lib,
    kea_testutils_lib,
    kea_util_unittests_lib,
]
kea_yang_tests = executable(
    'kea-yang-tests',
    'adaptor_config_unittests.cc',
    'adaptor_host_unittests.cc',
    'adaptor_option_unittests.cc',
    'adaptor_pool_unittests.cc',
    'adaptor_subnet_unittests.cc',
    'adaptor_unittests.cc',
    'config_unittests.cc',
    'run_unittests.cc',
    'translator_class_unittests.cc',
    'translator_control_socket_unittests.cc',
    'translator_database_unittests.cc',
    'translator_host_unittests.cc',
    'translator_logger_unittests.cc',
    'translator_option_data_unittests.cc',
    'translator_option_def_unittests.cc',
    'translator_pd_pool_unittests.cc',
    'translator_pool_unittests.cc',
    'translator_shared_network_unittests.cc',
    'translator_subnet_unittests.cc',
    'translator_unittests.cc',
    'translator_utils_unittests.cc',
    cpp_args: [f'-DCFG_EXAMPLES="@TOP_SOURCE_DIR@/doc/examples"'],
    dependencies: [NETCONF_DEP, GTEST_DEP],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: [kea_yang_tests_libs] + LIBS_BUILT_SO_FAR,
    override_options: ['cpp_std=c++20'],
)
test(
    'kea-yang-tests',
    kea_yang_tests,
    protocol: 'gtest',
    is_parallel: false,
    priority: -1,
)
