if not gtest.found() or not NETCONF_DEPS_FOUND
    subdir_done()
endif

sysrepo_setup_tests = executable(
    'kea-sysrepo-setup-tests',
    'sysrepo_setup_tests.cc',
    dependencies: NETCONF_DEPS_ARRAY + [gtest],
    include_directories: [include_directories('.')] + INCLUDES,
    override_options: ['cpp_std=c++20'],
)
test('kea-sysrepo-setup-tests', sysrepo_setup_tests)
