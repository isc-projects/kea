if not TESTS_OPT.enabled()
    subdir_done()
endif

dhcp_radius_libloadtests = executable(
    'dhcp-radius-libload-tests',
    'load_unload_unittests.cc',
    'run_unittests.cc',
    cpp_args: [
        f'-DTEST_DATA_BUILDDIR="@TOP_BUILD_DIR@/src/hooks/dhcp/radius/tests"',
        f'-DLIB_SO="@TOP_BUILD_DIR@/src/hooks/dhcp/radius/libdhcp_radius.so"',
        f'-DTEST_DICTIONARY="@TOP_SOURCE_DIR@/src/hooks/dhcp/radius/data/dictionary"',
    ],
    dependencies: [GTEST_DEP, CRYPTO_DEP],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
)
test(
    'dhcp-radius-libloadtests',
    dhcp_radius_libloadtests,
    depends: [dhcp_radius_lib],
    protocol: 'gtest',
)
