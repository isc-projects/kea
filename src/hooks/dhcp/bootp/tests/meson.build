if not gtest.found()
    subdir_done()
endif

HOOK_INCLUDES = [include_directories('..')]
dhcp_bootp_lib_tests = executable(
    'dhcp-bootp-lib-tests',
    'bootp_unittests.cc',
    'run_unittests.cc',
    cpp_args: [
        f'-DBOOTP_LIB_SO="@TOP_BUILD_DIR@/src/hooks/dhcp/bootp/libdhcp_bootp.so"',
    ],
    dependencies: [gtest],
    include_directories: [include_directories('.')] + INCLUDES + HOOK_INCLUDES,
    link_with: [dhcp_bootp_archive] + LIBS_BUILT_SO_FAR,
)
test('dhcp_bootp_lib_tests', dhcp_bootp_lib_tests, protocol: 'gtest')
