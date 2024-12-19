kea_eval_tests_exe = executable('kea-eval-tests',
  'boolean_unittest.cc',
  'context_unittest.cc',
  'dependency_unittest.cc',
  'evaluate_unittest.cc',
  'run_unittests.cc',
  'token_unittest.cc',
  dependencies: [gtest],
  include_directories: [include_directories('.')] + includes,
  link_with: libs_built_so_far + [kea_testutils_lib, kea_util_unittests_lib],
)
test('kea_eval_tests_exe', kea_eval_tests_exe)
