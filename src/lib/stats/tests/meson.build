if not gtest.found()
    subdir_done()
endif

kea_stats_tests = executable(
    'kea-stats-tests',
    'context_unittest.cc',
    'observation_unittest.cc',
    'run_unittests.cc',
    'stats_mgr_unittest.cc',
    dependencies: [gtest],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: [kea_testutils_lib, kea_util_unittests_lib] + LIBS_BUILT_SO_FAR,
)
test('kea_stats_tests', kea_stats_tests, protocol: 'gtest')
