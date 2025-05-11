kea_database_lib = shared_library(
    'kea-database',
    'audit_entry.cc',
    'backend_selector.cc',
    'database_connection.cc',
    'dbaccess_parser.cc',
    'db_log.cc',
    'db_messages.cc',
    'server.cc',
    'server_collection.cc',
    'server_selector.cc',
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: LIBDIR,
    install_rpath: INSTALL_RPATH,
    build_rpath: BUILD_RPATH,
    link_with: LIBS_BUILT_SO_FAR,
    version: '75.0.0',
)
LIBS_BUILT_SO_FAR = [kea_database_lib] + LIBS_BUILT_SO_FAR
subdir('testutils')
subdir('tests')
kea_database_headers = [
    'audit_entry.h',
    'backend_selector.h',
    'database_connection.h',
    'db_exceptions.h',
    'db_log.h',
    'db_messages.h',
    'dbaccess_parser.h',
    'server.h',
    'server_collection.h',
    'server_selector.h',
]
install_headers(
    kea_database_headers,
    preserve_path: true,
    subdir: 'kea/database',
)

if KEA_MSG_COMPILER.found()
    current_source_dir = meson.current_source_dir()
    target_gen_messages = run_target(
        'src-lib-database-db_messages',
        command: [
            CD_AND_RUN,
            TOP_SOURCE_DIR,
            KEA_MSG_COMPILER,
            'src/lib/database/db_messages.mes',
        ],
    )
    TARGETS_GEN_MESSAGES += [target_gen_messages]
endif
