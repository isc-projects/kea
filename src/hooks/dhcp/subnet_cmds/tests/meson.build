if not TESTS_OPT.enabled()
    subdir_done()
endif

dhcp_subnet_cmds_tests_libs = [dhcp_subnet_cmds_archive, kea_testutils_lib]
dhcp_subnet_cmds_tests = executable(
    'dhcp-subnet-cmds-tests',
    'run_unittests.cc',
    'subnet4_cmds_unittest.cc',
    'subnet6_cmds_unittest.cc',
    'subnet_cmds_unittest.cc',
    # tests using the DSO (vs archive) are being moved to libloadtests
    cpp_args: [
        f'-DLIB_SO="@TOP_BUILD_DIR@/src/hooks/dhcp/subnet_cmds/libdhcp_subnet_cmds.so"',
    ],
    dependencies: [CRYPTO_DEP, GTEST_DEP],
    include_directories: [include_directories('.'), include_directories('..')] + INCLUDES,
    link_with: [dhcp_subnet_cmds_tests_libs] + LIBS_BUILT_SO_FAR,
)
test('dhcp-subnet-cmds-tests', dhcp_subnet_cmds_tests, protocol: 'gtest')
