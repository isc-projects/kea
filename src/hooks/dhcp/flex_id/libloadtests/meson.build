if not gtest.found()
    subdir_done()
endif

current_build_dir = meson.current_build_dir()
dhcp_flex_id_libloadtests = executable(
    'dhcp-flex-id-libload-tests',
    'load_unload_unittests.cc',
    'run_unittests.cc',
    cpp_args: [
        f'-DTEST_DATA_BUILDDIR="@current_build_dir@"',
        f'-DLIB_SO="@TOP_BUILD_DIR@/src/hooks/dhcp/flex_id/libdhcp_flex_id.so"',
    ],
    dependencies: [gtest, crypto],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
)
test(
    'dhcp-flex-id-libloadtests',
    dhcp_flex_id_libloadtests,
    depends: [dhcp_flex_id_lib],
    protocol: 'gtest',
)
