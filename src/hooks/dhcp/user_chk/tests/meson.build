if not gtest.found()
    subdir_done()
endif

dhcp_user_chk_config_data = configuration_data()
dhcp_user_chk_config_data.set('abs_top_srcdir', TOP_SOURCE_DIR)
configure_file(
    input: 'test_data_files_config.h.in',
    output: 'test_data_files_config.h',
    configuration: dhcp_user_chk_config_data,
)

hook_includes = [include_directories('..')]
current_build_dir = meson.current_build_dir()
dhcp_user_chk_lib_tests = executable(
    'dhcp-user-chk-lib-tests',
    'run_unittests.cc',
    'user_file_unittests.cc',
    'user_registry_unittests.cc',
    'user_unittests.cc',
    'userid_unittests.cc',
    cpp_args: [f'-DTEST_DATA_BUILDDIR="@current_source_dir@"'],
    dependencies: [gtest],
    include_directories: [include_directories('.')] + INCLUDES + hook_includes,
    link_with: [dhcp_user_chk_archive] + LIBS_BUILT_SO_FAR,
)
test('dhcp_user_chk_lib_tests', dhcp_user_chk_lib_tests, protocol: 'gtest')
