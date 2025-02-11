if not gtest.found()
    subdir_done()
endif

sysrepo_setup_tests = executable(
    'kea-sysrepo-setup-tests',
    'sysrepo_setup_tests.cc',
    dependencies: netconf_deps_array,
    include_directories: [include_directories('.')] + INCLUDES,
)
test('sysrepo_setup_tests', sysrepo_setup_tests)
