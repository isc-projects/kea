dhcp_forensic_log_lib = shared_library(
    'dhcp_legal_log',
    'command_callouts.cc',
    'lease4_callouts.cc',
    'lease6_callouts.cc',
    'legal_log_log.cc',
    'legal_log_messages.cc',
    'load_unload.cc',
    'rotating_file.cc',
    'version.cc',
    cpp_args: [f'-DLEGAL_LOG_DIR="@LEGAL_LOG_DIR@"'],
    dependencies: [CRYPTO_DEP, MYSQL_DEP, POSTGRESQL_DEP],
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

if KEA_MSG_COMPILER.found()
    target_gen_messages = run_target(
        'src-hooks-dhcp-forensic_log-legal_log_messages',
        command: [
            CD_AND_RUN,
            TOP_SOURCE_DIR,
            KEA_MSG_COMPILER,
            'src/hooks/dhcp/forensic_log/legal_log_messages.mes',
        ],
    )
    TARGETS_GEN_MESSAGES += [target_gen_messages]
endif
