# todo: build without MySQL or PostgreSQL.

if not mysql.found() or not postgresql.found()
    subdir_done()
endif

dhcp_forensic_log_lib = shared_library(
    'dhcp_legal_log',
    'backend_store.cc',
    'command_callouts.cc',
    'lease4_callouts.cc',
    'lease6_callouts.cc',
    'legal_log_db_log.cc',
    'legal_log_log.cc',
    'legal_log_messages.cc',
    'load_unload.cc',
    'mysql_legal_log.cc',
    'pgsql_legal_log.cc',
    'rotating_file.cc',
    'version.cc',
    cpp_args: [f'-DLEGAL_LOG_DIR="@LEGAL_LOG_DIR@"'],
    dependencies: [crypto, mysql, postgresql],
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: 'lib/kea/hooks',
    link_with: LIBS_BUILT_SO_FAR,
    name_suffix: 'so',
)
dhcp_forensic_log_archive = static_library(
    'dhcp_forensic_log',
    objects: dhcp_forensic_log_lib.extract_all_objects(recursive: false),
)
subdir('libloadtests')
subdir('tests')
