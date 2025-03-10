if not TESTS_OPT.enabled()
    subdir_done()
endif

dhcp_host_cmds_tests_libs = [dhcp_host_cmds_archive, kea_dhcpsrv_testutils_lib]
dhcp_host_cmds_tests = executable(
    'dhcp-cmds-tests',
    'host_cmds_unittest.cc',
    'host_data_parser_unittest.cc',
    'run_unittests.cc',
    dependencies: [GTEST_DEP, CRYPTO_DEP],
    include_directories: [include_directories('.'), include_directories('..')] + INCLUDES,
    link_with: [dhcp_host_cmds_tests_libs] + LIBS_BUILT_SO_FAR,
)
test('dhcp-host-cmds-tests', dhcp_host_cmds_tests, protocol: 'gtest')
