if not TESTS_OPT.enabled()
    subdir_done()
endif

dhcp_cb_cmds_tests_libs = [
    dhcp_cb_cmds_archive,
    kea_dhcpsrv_testutils_lib,
    kea_dhcp_testutils_lib,
    kea_testutils_lib,
]
dhcp_cb_cmds_tests = executable(
    'dhcp-cb-cmds-tests',
    'client_class4_cmds_unittest.cc',
    'client_class6_cmds_unittest.cc',
    'global4_cmds_unittest.cc',
    'global6_cmds_unittest.cc',
    'option4_cmds_unittest.cc',
    'option4_network_cmds_unittest.cc',
    'option4_pool_cmds_unittest.cc',
    'option4_subnet_cmds_unittest.cc',
    'option6_cmds_unittest.cc',
    'option6_network_cmds_unittest.cc',
    'option6_pd_pool_cmds_unittest.cc',
    'option6_pool_cmds_unittest.cc',
    'option6_subnet_cmds_unittest.cc',
    'option_def4_cmds_unittest.cc',
    'option_def6_cmds_unittest.cc',
    'run_unittests.cc',
    'server4_cmds_unittest.cc',
    'server6_cmds_unittest.cc',
    'shared_network4_cmds_unittest.cc',
    'shared_network6_cmds_unittest.cc',
    'subnet4_cmds_unittest.cc',
    'subnet6_cmds_unittest.cc',
    dependencies: [GTEST_DEP, CRYPTO_DEP],
    include_directories: HINCLUDES + INCLUDES,
    link_with: [dhcp_cb_cmds_tests_libs] + LIBS_BUILT_SO_FAR,
)
test('dhcp-cb-cmds-tests', dhcp_cb_cmds_tests, protocol: 'gtest')
