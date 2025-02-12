if not gtest.found()
    subdir_done()
endif

current_build_dir = meson.current_build_dir()
dhcp_forensic_log_lltests_libs = [
    kea_mysql_testutils_lib,
    kea_pgsql_testutils_lib,
    kea_database_testutils_lib,
]
dhcp_forensic_log_libloadtests = executable(
    'dhcp-forensic-log-libload-tests',
    'load_unload_unittests.cc',
    'run_unittests.cc',
    cpp_args: [
        f'-DTEST_DATA_BUILDDIR="@current_build_dir@"',
        f'-DLEGAL_LOG_LIB_SO="@TOP_BUILD_DIR@/src/hooks/dhcp/forensic_log/libdhcp_legal_log.so"',
    ],
    dependencies: [gtest, crypto],
    include_directories: [include_directories('.'), include_directories('..')] + INCLUDES,
    link_with: [dhcp_forensic_log_lltests_libs] + LIBS_BUILT_SO_FAR,
)
test(
    'dhcp-forensic-log-libloadtests',
    dhcp_forensic_log_libloadtests,
    protocol: 'gtest',
)
