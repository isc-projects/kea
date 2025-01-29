kea_dhcp_ddns_tests = executable(
    'kea-dhcp_ddns-tests',
    'ncr_udp_unittests.cc',
    'ncr_unittests.cc',
    'run_unittests.cc',
    'test_utils.cc',
    'test_utils.h',
    dependencies: [gtest],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR + [kea_testutils_lib, kea_util_unittests_lib],
)
test('kea_dhcp_ddns_tests', kea_dhcp_ddns_tests, protocol: 'gtest')
