if not gtest.found()
    subdir_done()
endif

CURRENT_BUILD_DIR = meson.current_build_dir()
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
    dependencies: [gtest],
    cpp_args: [
        f'-DTEST_DATA_BUILDDIR="@CURRENT_BUILD_DIR@"',
        f'-DTEST_SCRIPT_SH="@CURRENT_BUILD_DIR@/process_test.sh"',
        f'-DDATA_DIR="@DHCP_DATA_DIR@"',
    ],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: [kea_util_unittests_lib] + libs_testutils + LIBS_BUILT_SO_FAR,
)
test('kea_process_tests', kea_process_tests, protocol: 'gtest')
