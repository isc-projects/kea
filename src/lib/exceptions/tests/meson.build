kea_exceptions_tests_exe = executable('kea-exceptions-tests',
  'exceptions_unittest.cc',
  'run_unittests.cc',
  dependencies: [gtest],
  include_directories: [include_directories('.')] + includes,
  link_with: libs_built_so_far,
)
test('kea_exceptions_tests_exe', kea_exceptions_tests_exe)
