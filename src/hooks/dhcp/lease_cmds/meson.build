dhcp_lease_cmds_lib = shared_library(
    'dhcp_lease_cmds',
    'binding_variables.cc',
    'lease_cmds.cc',
    'lease_cmds_callouts.cc',
    'lease_cmds_log.cc',
    'lease_cmds_messages.cc',
    'lease_parser.cc',
    'version.cc',
    dependencies: [crypto],
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: 'lib/kea/hooks',
    link_with: LIBS_BUILT_SO_FAR,
    name_suffix: 'so',
)
dhcp_lease_cmds_archive = static_library(
    'dhcp_lease_cmds',
    objects: dhcp_lease_cmds_lib.extract_all_objects(recursive: false),
)
subdir('libloadtests')
subdir('tests')

if HAS_KEA_MSG_COMPILER
    target_gen_messages = run_target(
        'src-hooks-dhcp-lease_cmds-lease_cmds_messages',
        command: [
            CD_AND_RUN,
            TOP_SOURCE_DIR,
            kea_msg_compiler,
            'src/hooks/dhcp/lease_cmds/lease_cmds_messages.mes',
        ],
    )
    TARGETS_GEN_MESSAGES += [target_gen_messages]
endif
