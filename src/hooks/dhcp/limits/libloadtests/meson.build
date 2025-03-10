if not TESTS_OPT.enabled()
    subdir_done()
endif

dhcp_limits_libloadtests = executable(
    'dhcp-limits-libload-tests',
    'limits_unit_tests_load_unload.cc',
    'limits_unit_tests_main.cc',
    cpp_args: [
        f'-DLIBDHCP_LIMITS_SO="@TOP_BUILD_DIR@/src/hooks/dhcp/limits/libdhcp_limits.so"',
    ],
    dependencies: [GTEST_DEP, CRYPTO_DEP],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
)
test(
    'dhcp-limits-libloadtests',
    dhcp_limits_libloadtests,
    depends: [dhcp_limits_lib],
    protocol: 'gtest',
)
