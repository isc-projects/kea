if not gtest.found()
    subdir_done()
endif

HOOK_INCLUDES = [include_directories('..')]
dhcp_bootp_libload_tests = executable(
    'dhcp-bootp-libload-tests',
    'load_unload_unittests.cc',
    'run_unittests.cc',
    cpp_args: [
        f'-DLIBDHCP_BOOTP_SO="@TOP_BUILD_DIR@/src/hooks/dhcp/bootp/libdhcp_bootp.so"',
    ],
    dependencies: [gtest, crypto],
    include_directories: [include_directories('.')] + INCLUDES + HOOK_INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
)
test('dhcp_bootp_libload_tests', dhcp_bootp_libload_tests, protocol: 'gtest')
