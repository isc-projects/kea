if not TESTS_OPT.enabled()
    subdir_done()
endif

dhcp_lease_cmds_lib_tests = executable(
    'dhcp-lease-cmds-lib-tests',
    'binding_variables_unittest.cc',
    'lease_cmds_func4_unittest.cc',
    'lease_cmds_func6_unittest.cc',
    'run_unittests.cc',
    dependencies: [GTEST_DEP, CRYPTO_DEP],
    include_directories: [include_directories('.'), include_directories('..')] + INCLUDES,
    link_with: [dhcp_lease_cmds_archive] + LIBS_BUILT_SO_FAR,
)
test('dhcp-lease-cmds-lib-tests', dhcp_lease_cmds_lib_tests, protocol: 'gtest')
