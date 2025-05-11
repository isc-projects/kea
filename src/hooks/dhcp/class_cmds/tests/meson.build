if not TESTS_OPT.enabled()
    subdir_done()
endif

dhcp_class_cmds_tests = executable(
    'dhcp-class-cmds-tests',
    'class_cmds_unittest.cc',
    'run_unittests.cc',
    dependencies: [GTEST_DEP, CRYPTO_DEP],
    include_directories: [include_directories('.'), include_directories('..')] + INCLUDES,
    link_with: [dhcp_class_cmds_archive] + LIBS_BUILT_SO_FAR,
)
test('dhcp-class-cmds-tests', dhcp_class_cmds_tests, protocol: 'gtest')
