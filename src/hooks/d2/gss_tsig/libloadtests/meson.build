if not gtest.found()
    subdir_done()
endif

current_source_dir = meson.current_source_dir()
ddns_gss_tsig_libloadtests = executable(
    'ddns-gss-tsig-libload-tests',
    'load_unload_unittests.cc',
    'run_unittests.cc',
    cpp_args: [
        f'-DTEST_DATA_BUILDDIR="@current_source_dir@"',
        f'-DLIBDHCP_GSS_TSIG_SO="@TOP_BUILD_DIR@/src/hooks/d2/gss_tsig/libddns_gss_tsig.so"',
    ],
    dependencies: [gtest, crypto],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
)
test('ddns-gss-tsig-libloadtests', ddns_gss_tsig_libloadtests, protocol: 'gtest')
