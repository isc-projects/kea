if not TESTS_OPT.enabled()
    subdir_done()
endif

libs_testutils = [
    kea_testutils_lib
]

dhcp_lease_cmds_libload_tests = executable(
    'dhcp-lease-cmds-libload-tests',
    'lease_cmds4_unittest.cc',
    'lease_cmds6_unittest.cc',
    'lease_cmds_unittest.cc',
    'load_unload_unittests.cc',
    'run_unittests.cc',
    cpp_args: [
        f'-DLIBDHCP_LEASE_CMDS_SO="@TOP_BUILD_DIR@/src/hooks/dhcp/lease_cmds/libdhcp_lease_cmds.so"',
    ],
    dependencies: [GTEST_DEP, CRYPTO_DEP],
    include_directories: [include_directories('.'), include_directories('..')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
    link_with: [libs_testutils] + LIBS_BUILT_SO_FAR,
)
test(
    'dhcp-lease-cmds-libload-tests',
    dhcp_lease_cmds_libload_tests,
    depends: [dhcp_lease_cmds_lib],
    protocol: 'gtest',
)
