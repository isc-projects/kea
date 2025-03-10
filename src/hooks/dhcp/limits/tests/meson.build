if not TESTS_OPT.enabled()
    subdir_done()
endif

dhcp_limits_tests = executable(
    'dhcp-limits-tests',
    'limits_unit_tests_lease_limiting.cc',
    'limits_unit_tests_limit_manager.cc',
    'limits_unit_tests_main.cc',
    'limits_unit_tests_rate_limiting.cc',
    dependencies: [CRYPTO_DEP, GTEST_DEP],
    include_directories: [include_directories('.'), include_directories('..')] + INCLUDES,
    link_with: [dhcp_limits_archive, kea_testutils_lib] + LIBS_BUILT_SO_FAR,
)
test('dhcp-limits-tests', dhcp_limits_tests, protocol: 'gtest')
