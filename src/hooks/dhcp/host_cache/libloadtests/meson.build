if not TESTS_OPT.enabled()
    subdir_done()
endif

current_build_dir = meson.current_build_dir()
dhcp_host_cache_libloadtests = executable(
    'dhcp-host-cache-libload-tests',
    'load_unload_unittests.cc',
    'run_unittests.cc',
    cpp_args: [
        f'-DTEST_DATA_BUILDDIR="@current_build_dir@"',
        f'-DLIB_SO="@TOP_BUILD_DIR@/src/hooks/dhcp/host_cache/libdhcp_host_cache.so"',
    ],
    dependencies: [GTEST_DEP, CRYPTO_DEP],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
)
test(
    'dhcp-host-cache-libloadtests',
    dhcp_host_cache_libloadtests,
    depends: [dhcp_host_cache_lib],
    protocol: 'gtest',
)
