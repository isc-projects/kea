if not gtest.found()
    subdir_done()
endif

kea_process_testutils_lib = static_library(
    'kea-process-testutils',
    'd_test_stubs.cc',
    cpp_args: [f'-DDATABASE_SCRIPTS_DIR="@DATABASE_SCRIPTS_DIR@"'],
    dependencies: [boost],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
)
