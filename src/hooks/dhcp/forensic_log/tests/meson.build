if not TESTS_OPT.enabled()
    subdir_done()
endif

configure_file(
    input: 'forensic_postrotate_test.sh.in',
    output: 'forensic_postrotate_test.sh',
    copy: true,
)
configure_file(
    input: 'forensic_prerotate_test.sh.in',
    output: 'forensic_prerotate_test.sh',
    copy: true,
)

current_build_dir = meson.current_build_dir()

dependencies = [GTEST_DEP, CRYPTO_DEP]

dhcp_forensic_log_tests_libs = [
    dhcp_forensic_log_archive,
    kea_dhcpsrv_testutils_lib,
    kea_database_testutils_lib,
    kea_testutils_lib,
]

sources = [
    'dhcp-forensic-log-tests',
    'legal_log_mgr_unittests.cc',
    'command_log_unittests.cc',
    'legal_log4_unittests.cc',
    'legal_log6_unittests.cc',
    'rotating_file_unittests.cc',
    'run_unittests.cc',
]

dhcp_forensic_log_tests = executable(
    sources,
    cpp_args: [
        f'-DTEST_DATA_BUILDDIR="@current_build_dir@"',
        f'-DFORENSIC_PREROTATE_TEST_SH="@current_build_dir@/forensic_prerotate_test.sh"',
        f'-DINVALID_FORENSIC_PREROTATE_TEST_SH="@TOP_SOURCE_DIR@/README"',
        f'-DFORENSIC_POSTROTATE_TEST_SH="@current_build_dir@/forensic_postrotate_test.sh"',
        f'-DINVALID_FORENSIC_POSTROTATE_TEST_SH="@TOP_SOURCE_DIR@/README"',
        f'-DLEGAL_LOG_DIR="@LEGAL_LOG_DIR@"',
    ],
    dependencies: dependencies,
    include_directories: [include_directories('.'), include_directories('..')] + INCLUDES,
    link_with: [dhcp_forensic_log_tests_libs] + LIBS_BUILT_SO_FAR,
)
test(
    'dhcp-forensic-log-tests',
    dhcp_forensic_log_tests,
    protocol: 'gtest',
    timeout: 60,
)
