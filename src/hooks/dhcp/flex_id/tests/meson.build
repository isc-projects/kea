if not TESTS_OPT.enabled()
    subdir_done()
endif

current_build_dir = meson.current_build_dir()
dhcp_flex_id_tests = executable(
    'dhcp-flex-id-tests',
    'callout_unittests.cc',
    'run_unittests.cc',
    cpp_args: [f'-DTEST_DATA_BUILDDIR="@current_build_dir@"'],
    dependencies: [GTEST_DEP],
    include_directories: [include_directories('.'), include_directories('..')] + INCLUDES,
    link_with: [dhcp_flex_id_archive] + LIBS_BUILT_SO_FAR,
)
test('dhcp-flex-id-tests', dhcp_flex_id_tests, protocol: 'gtest')
