kea_dhcp_ddns_tests_exe = executable('kea-dhcp_ddns-tests',
  'ncr_udp_unittests.cc',
  'ncr_unittests.cc',
  'run_unittests.cc',
  'test_utils.cc',
  'test_utils.h',
  dependencies: [gtest],
  include_directories: [include_directories('.')] + includes,
  link_with: libs_built_so_far + [kea_testutils_lib, kea_util_unittests_lib],
)
test('kea_dhcp_ddns_tests_exe', kea_dhcp_ddns_tests_exe)
