if not gtest.found()
    subdir_done()
endif

dhcp_ddns_tuning_libloadtests = executable(
    'dhcp-ddns-tuning-libload-tests',
    'callout4_unittests.cc',
    'callout6_unittests.cc',
    'callout_unittests.cc',
    'load_unload_unittests.cc',
    'run_unittests.cc',
    cpp_args: [
        f'-DDDNS_TUNING_LIB_SO="@TOP_BUILD_DIR@/src/hooks/dhcp/ddns_tuning/libdhcp_ddns_tuning.so"',
    ],
    dependencies: [gtest, crypto],
    include_directories: [include_directories('.'), include_directories('..')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
)
test(
    'dhcp-ddns-tuning-libloadtests',
    dhcp_ddns_tuning_libloadtests,
    depends: [dhcp_ddns_tuning_lib],
    protocol: 'gtest',
)
