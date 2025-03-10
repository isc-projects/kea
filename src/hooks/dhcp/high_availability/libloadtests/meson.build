if not TESTS_OPT.enabled()
    subdir_done()
endif

dhcp_ha_libload_tests = executable(
    'dhcp-ha-libload-tests',
    'close_unittests.cc',
    'load_unload_unittests.cc',
    'run_unittests.cc',
    cpp_args: [
        f'-DLIBDHCP_HA_SO="@TOP_BUILD_DIR@/src/hooks/dhcp/high_availability/libdhcp_ha.so"',
    ],
    dependencies: [GTEST_DEP, CRYPTO_DEP],
    include_directories: [include_directories('.'), include_directories('..')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
)
test(
    'dhcp-ha-libload-tests',
    dhcp_ha_libload_tests,
    depends: [dhcp_ha_lib],
    protocol: 'gtest',
)
