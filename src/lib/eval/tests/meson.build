if not gtest.found()
    subdir_done()
endif

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
    link_with: [kea_testutils_lib, kea_util_unittests_lib] + LIBS_BUILT_SO_FAR,
)
test('kea_eval_tests', kea_eval_tests, protocol: 'gtest')
