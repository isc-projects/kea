kea_stats_tests_exe = executable('kea-stats-tests',
  'context_unittest.cc',
  'observation_unittest.cc',
  'run_unittests.cc',
  'stats_mgr_unittest.cc',
  dependencies: [gtest],
  include_directories: [include_directories('.')] + includes,
  link_with: libs_built_so_far + [kea_testutils_lib, kea_util_unittests_lib],
)
test('kea_stats_tests_exe', kea_stats_tests_exe)
