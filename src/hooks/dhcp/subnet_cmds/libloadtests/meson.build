if not TESTS_OPT.enabled()
    subdir_done()
endif

dhcp_subnet_cmds_libloadtests = executable(
    'dhcp-subnet-cmds-libload-tests',
    'load_unload_unittests.cc',
    'run_unittests.cc',
    cpp_args: [
        f'-DLIBDHCP_SUBNET_CMDS_SO="@TOP_BUILD_DIR@/src/hooks/dhcp/subnet_cmds/libdhcp_subnet_cmds.so"',
    ],
    dependencies: [GTEST_DEP, CRYPTO_DEP],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
)
test(
    'dhcp-subnet-cmds-libloadtests',
    dhcp_subnet_cmds_libloadtests,
    depends: [dhcp_subnet_cmds_lib],
    protocol: 'gtest',
)
