if not gtest.found() or not krb5.found()
    subdir_done()
endif

current_source_dir = meson.current_source_dir()
ddns_gss_tsig_tests_libs = [
    ddns_gss_tsig_testutils_lib,
    ddns_gss_tsig_archive,
    kea_d2srv_testutils_lib,
    kea_testutils_lib,
]
ddns_gss_tsig_tests = executable(
    'ddns-gss-tsig-tests',
    'dns_update_unittests.cc',
    'gss_tsig_api_unittests.cc',
    'gss_tsig_callouts_unittests.cc',
    'gss_tsig_cfg_unittests.cc',
    'gss_tsig_context_unittests.cc',
    'gss_tsig_impl_unittests.cc',
    'gss_tsig_key_unittests.cc',
    'managed_key_unittests.cc',
    'run_unittests.cc',
    'tkey_exchange_unittests.cc',
    'tkey_unittests.cc',
    cpp_args: [f'-DTEST_DATA_DIR="@current_source_dir@"'],
    dependencies: [krb5, gtest, crypto],
    include_directories: [include_directories('.'), include_directories('..')] + INCLUDES,
    link_with: [ddns_gss_tsig_tests_libs] + LIBS_BUILT_SO_FAR,
)
test('ddns-gss-tsig-tests', ddns_gss_tsig_tests, protocol: 'gtest')

executable(
    'nsupdate',
    'nsupdate.cc',
    cpp_args: [f'-DTEST_DATA_DIR="@current_source_dir@"'],
    dependencies: [krb5],
    include_directories: [include_directories('.'), include_directories('..')] + INCLUDES,
    link_with: [ddns_gss_tsig_archive] + LIBS_BUILT_SO_FAR,
)
