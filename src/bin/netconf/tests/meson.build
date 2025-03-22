if not TESTS_OPT.enabled() or not NETCONF_DEP.found()
    subdir_done()
endif

current_build_dir = meson.current_build_dir()
current_source_dir = meson.current_source_dir()

basic = shared_library(
    'basic',
    'basic_library.cc',
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
    build_rpath: '/nowhere',
    name_suffix: 'so',
)

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
    cpp_args: [
        f'-DBASIC_CALLOUT_LIBRARY="@current_build_dir@/libbasic.so"',
        f'-DCFG_EXAMPLES="@TOP_SOURCE_DIR@/doc/examples/netconf"',
        '-DKEATEST_MODULE',
        f'-DSYNTAX_FILE="@current_source_dir@/../netconf_parser.yy"',
        f'-DTEST_DATA_SOURCEDIR="@current_source_dir@"',
        f'-DTEST_DATA_BUILDDIR="@current_build_dir@"',
    ],
    dependencies: [NETCONF_DEP, GTEST_DEP, CRYPTO_DEP],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: [
        netconf_lib,
        kea_yang_testutils_lib,
        kea_process_testutils_lib,
        kea_testutils_lib,
    ] + LIBS_BUILT_SO_FAR,
)
test(
    'kea-netconf-tests',
    kea_netconf_tests,
    depends: [basic],
    protocol: 'gtest',
    is_parallel: false,
    priority: -1,
)

subdir('shtests')
