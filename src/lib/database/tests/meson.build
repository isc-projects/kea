kea_database_tests_exe = executable('kea-database-tests',
  'audit_entry_unittest.cc',
  'backend_selector_unittest.cc',
  'database_connection_unittest.cc',
  'database_log_unittest.cc',
  'dbaccess_parser_unittest.cc',
  'run_unittests.cc',
  'server_selector_unittest.cc',
  'server_unittest.cc',
  dependencies: [gtest],
  include_directories: [include_directories('.')] + includes,
  link_with: libs_built_so_far + [kea_testutils_lib, kea_util_unittests_lib],
)
test('kea_database_tests_exe', kea_database_tests_exe)
