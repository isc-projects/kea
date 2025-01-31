DATABASE_SCRIPTS_DIR = f'@TOP_BUILD_DIR@/src/share/database/scripts'
kea_mysql_testutils_lib = static_library(
    'kea-mysql-testutils',
    'mysql_schema.cc',
    cpp_args: [f'-DDATABASE_SCRIPTS_DIR="@DATABASE_SCRIPTS_DIR@"',
               f'-DDATABASE_WIPE_DIR="@DATABASE_SCRIPTS_DIR@"'],
    dependencies: [mysql],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR + [kea_database_testutils_lib]
)
