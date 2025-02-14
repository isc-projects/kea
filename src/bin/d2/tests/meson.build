if not gtest.found()
    subdir_done()
endif

current_build_dir = meson.current_build_dir()

kea_d2_tests = executable(
    'kea-d2-tests',
    'check_exists_add.cc',
    'check_exists_remove.cc',
    'd2_controller.cc',
    'd2_lexer.cc',
    'd2_parser.cc',
    'd2_process.cc',
    'd2_queue_mgr.cc',
    'd2_update_mgr.cc',
    'main.cc',
    'nc_add.cc',
    'nc_remove.cc',
    'parser_context.cc',
    'simple_add.cc',
    'simple_add_without_dhcid.cc',
    'simple_remove.cc',
    'simple_remove_without_dhcid.cc',
    cpp_args: [
        f'-DCFG_EXAMPLES="@TOP_SOURCE_DIR@/doc/examples/ddns"',
        f'-DSYNTAX_FILE="@current_source_dir@/../d2_parser.yy"',
        f'-DTEST_CA_DIR="@TEST_CA_DIR@"',
        f'-DTEST_DATA_BUILDDIR="@current_build_dir@"',
    ],
    dependencies: [gtest],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: [d2_lib] + LIBS_BUILT_SO_FAR,
)
test('kea-d2-tests', kea_d2_tests, protocol: 'gtest')
