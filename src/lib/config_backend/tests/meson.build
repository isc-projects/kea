kea_config_backend_tests_exe = executable('kea-config_backend-tests',
  'config_backend_mgr_unittest.cc',
  'run_unittests.cc',
  dependencies: [gtest],
  include_directories: [include_directories('.')] + includes,
  link_with: libs_built_so_far + [kea_testutils_lib, kea_util_unittests_lib],
)
test('kea_config_backend_tests_exe', kea_config_backend_tests_exe)
