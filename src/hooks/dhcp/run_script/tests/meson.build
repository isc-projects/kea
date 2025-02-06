if not gtest.found()
    subdir_done()
endif

run_script_test_conf_data = configuration_data()
run_script_test_conf_data.set('abs_top_builddir', TOP_BUILD_DIR)
configure_file(
    input: 'run_script_test.sh.in',
    output: 'run_script_test.sh',
    configuration: run_script_test_conf_data,
)

CURRENT_BUILD_DIR = meson.current_build_dir()
HOOK_INCLUDES = [include_directories('..')]
dhcp_run_script_lib_tests = executable(
    'dhcp-run-script-lib-tests',
    'run_script_unittests.cc',
    'run_unittests.cc',
    cpp_args: [
        f'-DRUN_SCRIPT_LIB_SO="@TOP_BUILD_DIR@/src/hooks/dhcp/run_script/libdhcp_run_script.so"',
        f'-DTEST_LOG_FILE="@CURRENT_BUILD_DIR@/test.log"',
        f'-DRUN_SCRIPT_TEST_SH="@CURRENT_BUILD_DIR@/run_script_test.sh"',
    ],
    dependencies: [gtest, crypto],
    include_directories: [include_directories('.')] + INCLUDES + HOOK_INCLUDES,
    link_with: [dhcp_run_script_archive] + LIBS_BUILT_SO_FAR,
)
test('dhcp_run_script_lib_tests', dhcp_run_script_lib_tests, protocol: 'gtest')
