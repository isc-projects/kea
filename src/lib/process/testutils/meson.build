if not TESTS_OPT.enabled()
    subdir_done()
endif

kea_process_testutils_lib = static_library(
    'kea-process-testutils',
    'd_test_stubs.cc',
    cpp_args: [f'-DDATABASE_SCRIPTS_DIR="@DATABASE_SCRIPTS_DIR@"'],
    dependencies: [GTEST_DEP],
    include_directories: [include_directories('.')] + INCLUDES,
)
