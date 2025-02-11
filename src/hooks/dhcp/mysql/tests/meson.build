if not gtest.found()
    subdir_done()
endif

libs_testutils = [
    kea_dhcpsrv_testutils_lib,
    kea_mysql_testutils_lib,
    kea_database_testutils_lib,
]
dhcp_mysql_lib_tests = executable(
    'dhcp-mysql-lib-tests',
    'mysql_bootp_unittest.cc',
    'mysql_cb_dhcp4_mgr_unittest.cc',
    'mysql_cb_dhcp4_unittest.cc',
    'mysql_cb_dhcp6_mgr_unittest.cc',
    'mysql_cb_dhcp6_unittest.cc',
    'mysql_cb_impl_unittest.cc',
    'mysql_host_data_source_unittest.cc',
    'mysql_lease_extended_info_unittest.cc',
    'mysql_lease_mgr_unittest.cc',
    'run_unittests.cc',
    dependencies: [gtest, crypto, mysql],
    include_directories: [include_directories('.'), include_directories('..')] + INCLUDES,
    link_with: [dhcp_mysql_archive] + libs_testutils + LIBS_BUILT_SO_FAR,
)
test(
    'dhcp_mysql_lib_tests',
    dhcp_mysql_lib_tests,
    protocol: 'gtest',
    is_parallel: false,
)
