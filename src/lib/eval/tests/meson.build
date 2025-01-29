kea_eval_tests = executable(
    'kea-eval-tests',
    'boolean_unittest.cc',
    'context_unittest.cc',
    'dependency_unittest.cc',
    'evaluate_unittest.cc',
    'run_unittests.cc',
    'token_unittest.cc',
    dependencies: [gtest],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR + [kea_testutils_lib, kea_util_unittests_lib],
)
test('kea_eval_tests', kea_eval_tests, protocol: 'gtest')
