kea_stats_tests = executable(
    'kea-stats-tests',
    'context_unittest.cc',
    'observation_unittest.cc',
    'run_unittests.cc',
    'stats_mgr_unittest.cc',
    dependencies: [gtest],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR + [kea_testutils_lib, kea_util_unittests_lib],
)
test('kea_stats_tests', kea_stats_tests, protocol: 'gtest')
