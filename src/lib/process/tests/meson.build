if not TESTS_OPT.enabled()
    subdir_done()
endif

current_build_dir = meson.current_build_dir()
libs_testutils = [kea_process_testutils_lib, kea_testutils_lib]
configure_file(
    input: 'process_test.sh.in',
    output: 'process_test.sh',
    copy: true,
)
kea_process_tests = executable(
    'kea-process-tests',
    'cb_ctl_base_unittests.cc',
    'config_base_unittests.cc',
    'config_ctl_info_unittests.cc',
    'config_ctl_parser_unittests.cc',
    'd_cfg_mgr_unittests.cc',
    'd_controller_unittests.cc',
    'daemon_unittest.cc',
    'log_parser_unittests.cc',
    'logging_info_unittests.cc',
    'run_unittests.cc',
    dependencies: [GTEST_DEP],
    cpp_args: [
        f'-DTEST_DATA_BUILDDIR="@current_build_dir@"',
        f'-DTEST_SCRIPT_SH="@current_build_dir@/process_test.sh"',
        f'-DPIDFILE_DIR="@PREFIX@/@LOCALSTATEDIR@/run/kea"',
    ],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: [kea_util_unittests_lib, libs_testutils] + LIBS_BUILT_SO_FAR,
)
test('kea-process-tests', kea_process_tests, protocol: 'gtest')
