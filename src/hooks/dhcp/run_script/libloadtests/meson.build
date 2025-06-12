if not TESTS_OPT.enabled()
    subdir_done()
endif
hook_includes = [include_directories('..')]
dhcp_run_script_libload_tests = executable(
    'dhcp-run-script-libload-tests',
    'load_unload_unittests.cc',
    'run_unittests.cc',
    cpp_args: [
        f'-DTEST_DATA_BUILDDIR="@current_build_dir@"',
        f'-DLIBRUN_SCRIPT_SO="@TOP_BUILD_DIR@/src/hooks/dhcp/run_script/libdhcp_run_script.so"',
        f'-DRUN_SCRIPT_TEST_SH="@TOP_BUILD_DIR@/src/hooks/dhcp/run_script/tests/run_script_test.sh"',
    ],
    dependencies: [GTEST_DEP, CRYPTO_DEP],
    include_directories: [include_directories('.'), include_directories('..')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
)
test(
    'dhcp-run-script-libload-tests',
    dhcp_run_script_libload_tests,
    depends: [dhcp_run_script_lib],
    protocol: 'gtest',
)
