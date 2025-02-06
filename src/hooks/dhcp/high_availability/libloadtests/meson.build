if not gtest.found()
    subdir_done()
endif

HOOK_INCLUDES = [include_directories('..')]
dhcp_ha_libload_tests = executable(
    'dhcp-ha-libload-tests',
    'close_unittests.cc',
    'load_unload_unittests.cc',
    'run_unittests.cc',
    cpp_args: [
        f'-DLIBDHCP_HA_SO="@TOP_BUILD_DIR@/src/hooks/dhcp/high_availability/libdhcp_ha.so"',
    ],
    dependencies: [gtest, crypto],
    include_directories: [include_directories('.')] + INCLUDES + HOOK_INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
)
test('dhcp_ha_libload_tests', dhcp_ha_libload_tests, protocol: 'gtest')
