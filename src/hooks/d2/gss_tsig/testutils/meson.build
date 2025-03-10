if not TESTS_OPT.enabled()
    subdir_done()
endif

current_source_dir = meson.current_source_dir()
ddns_gss_tsig_testutils_lib = static_library(
    'ddns-gss-tsig-testutils',
    'gss_tsig_dns_server.cc',
    cpp_args: [f'-DTEST_DATA_DIR="@current_source_dir@"'],
    dependencies: [GTEST_DEP, CRYPTO_DEP],
    include_directories: [include_directories('.'), include_directories('..')] + INCLUDES,
)
