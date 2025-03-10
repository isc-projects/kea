if not TESTS_OPT.enabled()
    subdir_done()
endif

dhcp_ddns_tuning_tests = executable(
    'dhcp-ddns-tuning-tests',
    'ddns_tuning_unittests.cc',
    'expression_cache_unittests.cc',
    'run_unittests.cc',
    dependencies: [GTEST_DEP, CRYPTO_DEP],
    include_directories: [include_directories('.'), include_directories('..')] + INCLUDES,
    link_with: [dhcp_ddns_tuning_archive] + LIBS_BUILT_SO_FAR,
)
test('dhcp-ddns-tuning-tests', dhcp_ddns_tuning_tests, protocol: 'gtest')
