if not TESTS_OPT.enabled() or not POSTGRESQL_DEP.found()
    subdir_done()
endif

kea_pgsql_testutils_lib = static_library(
    'kea-pgsql-testutils',
    'pgsql_schema.cc',
    cpp_args: [
        f'-DDATABASE_SCRIPTS_DIR="@DATABASE_SCRIPTS_DIR@"',
        f'-DDATABASE_WIPE_DIR="@DATABASE_SCRIPTS_DIR@"',
    ],
    dependencies: [GTEST_DEP, POSTGRESQL_DEP],
    include_directories: [include_directories('.')] + INCLUDES,
)
