if not TESTS_OPT.enabled()
    subdir_done()
endif

kea_database_testutils_lib = static_library(
    'kea-database-testutils',
    'schema.cc',
    cpp_args: [f'-DTEST_CA_DIR="@TEST_CA_DIR@"'],
    dependencies: [GTEST_DEP],
    include_directories: [include_directories('.')] + INCLUDES,
)
