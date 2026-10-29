if not TESTS_OPT.enabled()
    subdir_done()
endif

dhcp_rbac_libloadtests = executable(
    'dhcp-rbac-libload-tests',
    'load_unload_unittests.cc',
    'run_unittests.cc',
    cpp_args: [
        f'-DRBAC_LIB_SO="@TOP_BUILD_DIR@/src/hooks/dhcp/rbac/libdhcp_rbac.so"',
        f'-DAPI_DIR="@TOP_SOURCE_DIR@/src/share/api"',
    ],
    dependencies: [GTEST_DEP, CRYPTO_DEP],
    include_directories: HINCLUDES + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
)
test(
    'dhcp-rbac-libload-tests',
    dhcp_rbac_libloadtests,
    depends: [dhcp_rbac_lib],
    protocol: 'gtest',
)
