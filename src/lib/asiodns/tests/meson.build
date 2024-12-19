kea_asiodns_tests_exe = executable('kea-asiodns-tests',
  'io_fetch_unittest.cc',
  'run_unittests.cc',
  dependencies: [gtest],
  include_directories: [include_directories('.')] + includes,
  link_with: libs_built_so_far + [kea_testutils_lib, kea_util_unittests_lib],
)
test('kea_asiodns_tests_exe', kea_asiodns_tests_exe)
