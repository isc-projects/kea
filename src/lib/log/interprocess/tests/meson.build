if not gtest.found()
    subdir_done()
endif

kea_log_interprocess_tests = executable(
    'kea-log-interprocess-tests',
    'interprocess_sync_file_unittest.cc',
    'interprocess_sync_null_unittest.cc',
    'run_unittests.cc',
    cpp_args: [f'-DTEST_DATA_TOPBUILDDIR="@TOP_BUILD_DIR@"'],
    dependencies: [gtest],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: [kea_util_unittests_lib] + LIBS_BUILT_SO_FAR,
)
test('kea_log_interprocess_tests', kea_log_interprocess_tests, protocol: 'gtest')
