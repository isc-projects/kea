if not postgresql.found() or not postgresql_server_header.found()
    subdir_done()
endif

kea_pgsql_lib = library(
    'kea-pgsql',
    'pgsql_connection.cc',
    'pgsql_connection.h',
    'pgsql_exchange.cc',
    'pgsql_exchange.h',
    cpp_args: [f'-DKEA_ADMIN="@KEA_ADMIN@"'],
    dependencies: [postgresql, postgresql_server_header],
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: 'lib',
    link_with: LIBS_BUILT_SO_FAR,
)
LIBS_BUILT_SO_FAR = [kea_pgsql_lib] + LIBS_BUILT_SO_FAR
