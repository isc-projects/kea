if not gtest.found()
    subdir_done()
endif

kea_mysql_testutils_lib = static_library(
    'kea-mysql-testutils',
    'mysql_schema.cc',
    cpp_args: [
        f'-DDATABASE_SCRIPTS_DIR="@DATABASE_SCRIPTS_DIR@"',
        f'-DDATABASE_WIPE_DIR="@DATABASE_SCRIPTS_DIR@"',
    ],
    dependencies: [gtest, mysql],
    include_directories: [include_directories('.')] + INCLUDES,
)
