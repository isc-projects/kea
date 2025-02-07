if not gtest.found()
    subdir_done()
endif

sources = [
    'alloc_engine_utils.cc',
    'concrete_lease_mgr.cc',
    'config_result_check.cc',
    'dhcp4o6_test_ipc.cc',
    'generic_backend_unittest.cc',
    'generic_cb_dhcp4_unittest.cc',
    'generic_cb_dhcp6_unittest.cc',
    'generic_cb_recovery_unittest.cc',
    'generic_host_data_source_unittest.cc',
    'generic_lease_mgr_unittest.cc',
    'host_data_source_utils.cc',
    'lease_file_io.cc',
    'memory_host_data_source.cc',
    'test_config_backend_dhcp4.cc',
    'test_config_backend_dhcp6.cc',
    'test_utils.cc',
]
dependencies = [boost, crypto]
if mysql.found()
    sources += ['mysql_generic_backend_unittest.cc']
    dependencies += [mysql]
endif
if postgresql.found()
    sources += ['pgsql_generic_backend_unittest.cc']
    dependencies += [postgresql]
endif
kea_dhcpsrv_testutils_lib = static_library(
    'kea-dhcpsrv-testutils',
    sources,
    cpp_args: [f'-DDATABASE_SCRIPTS_DIR="@DATABASE_SCRIPTS_DIR@"'],
    dependencies: dependencies,
    include_directories: [include_directories('.')] + INCLUDES,
)
