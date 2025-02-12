if not gtest.found()
    subdir_done()
endif

dhcp_class_cmds_libloadtests = executable(
    'dhcp-class-cmds-libload-tests',
    'load_unload_unittests.cc',
    'run_unittests.cc',
    cpp_args: [
        f'-DLIBDHCP_CLASS_CMDS_SO="@TOP_BUILD_DIR@/src/hooks/dhcp/class_cmds/libdhcp_class_cmds.so"',
    ],
    dependencies: [gtest, crypto],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
)
test(
    'dhcp-class-cmds-libloadtests',
    dhcp_class_cmds_libloadtests,
    protocol: 'gtest',
)
