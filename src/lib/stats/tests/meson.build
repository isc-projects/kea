if not TESTS_OPT.enabled()
    subdir_done()
endif

kea_stats_tests = executable(
    'kea-stats-tests',
    'context_unittest.cc',
    'observation_unittest.cc',
    'run_unittests.cc',
    'stats_mgr_unittest.cc',
    dependencies: [GTEST_DEP],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: [kea_testutils_lib, kea_util_unittests_lib] + LIBS_BUILT_SO_FAR,
)
test('kea-stats-tests', kea_stats_tests, protocol: 'gtest')
