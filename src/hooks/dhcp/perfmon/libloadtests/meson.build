if not gtest.found()
    subdir_done()
endif

HOOK_INCLUDES = [include_directories('..')]
dhcp_perfmon_libload_tests = executable(
    'dhcp-perfmon-libload-tests',
    'load_unload_unittests.cc',
    'run_unittests.cc',
    cpp_args: [
        f'-DLIBDHCP_PERFMON_SO="@TOP_BUILD_DIR@/src/hooks/dhcp/perfmon/libdhcp_perfmon.so"',
    ],
    dependencies: [gtest, crypto],
    include_directories: [include_directories('.')] + INCLUDES + HOOK_INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
)
test('dhcp_perfmon_libload_tests', dhcp_perfmon_libload_tests, protocol: 'gtest')
