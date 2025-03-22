if not TESTS_OPT.enabled() or not NETCONF_DEP.found()
    subdir_done()
endif

sysrepo_setup_tests = executable(
    'kea-sysrepo-setup-tests',
    'sysrepo_setup_tests.cc',
    dependencies: [NETCONF_DEP, GTEST_DEP],
    include_directories: [include_directories('.')] + INCLUDES,
)
test('kea-sysrepo-setup-tests', sysrepo_setup_tests)
