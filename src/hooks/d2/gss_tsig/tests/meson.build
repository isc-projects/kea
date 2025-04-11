if not TESTS_OPT.enabled() or not KRB5_DEP.found()
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
    dependencies: [KRB5_DEP, GTEST_DEP, CRYPTO_DEP],
    include_directories: [include_directories('.'), include_directories('..')] + INCLUDES,
    link_with: [ddns_gss_tsig_tests_libs] + LIBS_BUILT_SO_FAR,
)
test('ddns-gss-tsig-tests', ddns_gss_tsig_tests, protocol: 'gtest')

executable(
    'nsupdate',
    'nsupdate.cc',
    cpp_args: [f'-DTEST_DATA_DIR="@current_source_dir@"'],
    dependencies: [KRB5_DEP],
    include_directories: [include_directories('.'), include_directories('..')] + INCLUDES,
    link_with: [ddns_gss_tsig_archive] + LIBS_BUILT_SO_FAR,
)

# Heimdal requires restricted permissions on the credential cache files.
foreach ccache : ['administrator.ccache', 'testdenied.ccache']
    configure_file(
        command: ['chmod', 'go-rw', f'@current_source_dir@/@ccache@'],
        input: f'@ccache@',
        output: f'@ccache@',
    )
endforeach
