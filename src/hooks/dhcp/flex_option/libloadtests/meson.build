if not gtest.found()
    subdir_done()
endif

dhcp_flex_option_libload_tests = executable(
    'dhcp-flex-option-libload-tests',
    'callout_unittests.cc',
    'load_unload_unittests.cc',
    'run_unittests.cc',
    cpp_args: [
        f'-DFLEX_OPTION_LIB_SO="@TOP_BUILD_DIR@/src/hooks/dhcp/flex_option/libdhcp_flex_option.so"',
    ],
    dependencies: [gtest, crypto],
    include_directories: [include_directories('.'), include_directories('..')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
)
test(
    'dhcp_flex_option_libload_tests',
    dhcp_flex_option_libload_tests,
    protocol: 'gtest',
)
