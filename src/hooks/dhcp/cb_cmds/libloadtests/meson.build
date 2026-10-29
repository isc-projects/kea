if not TESTS_OPT.enabled()
    subdir_done()
endif

dhcp_cb_cmds_libloadtests = executable(
    'dhcp-cb-cmds-libload-tests',
    'load_unload_unittests.cc',
    'run_unittests.cc',
    cpp_args: [
        f'-DLIBDHCP_CB_CMDS_SO="@TOP_BUILD_DIR@/src/hooks/dhcp/cb_cmds/libdhcp_cb_cmds.so"',
    ],
    dependencies: [GTEST_DEP, CRYPTO_DEP],
    include_directories: HINCLUDES + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
)
test(
    'dhcp-cb-cmds-libload-tests',
    dhcp_cb_cmds_libloadtests,
    depends: [dhcp_cb_cmds_lib],
    protocol: 'gtest',
)
