DATABASE_SCRIPTS_DIR = f'@TOP_BUILD_DIR@/src/share/database/scripts'
kea_pgsql_testutils_lib = static_library(
    'kea-pgsql-testutils',
    'pgsql_schema.cc',
    cpp_args: [
        f'-DDATABASE_SCRIPTS_DIR="@DATABASE_SCRIPTS_DIR@"',
        f'-DDATABASE_WIPE_DIR="@DATABASE_SCRIPTS_DIR@"',
    ],
    dependencies: [postgresql],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: [kea_database_testutils_lib] + LIBS_BUILT_SO_FAR,
)
