if not TESTS_OPT.enabled()
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
    dependencies: [GTEST_DEP, CRYPTO_DEP],
    include_directories: [include_directories('.'), include_directories('..')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
)
test(
    'dhcp-flex-option-libload-tests',
    dhcp_flex_option_libload_tests,
    depends: [dhcp_flex_option_lib],
    protocol: 'gtest',
)
