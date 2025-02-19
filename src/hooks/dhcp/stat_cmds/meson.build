dhcp_stat_cmds_lib = shared_library(
    'dhcp_stat_cmds',
    'stat_cmds.cc',
    'stat_cmds_callouts.cc',
    'stat_cmds_log.cc',
    'stat_cmds_messages.cc',
    'version.cc',
    dependencies: [crypto],
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: 'lib/kea/hooks',
    link_with: LIBS_BUILT_SO_FAR,
    name_suffix: 'so',
)
dhcp_stat_cmds_archive = static_library(
    'dhcp_stat_cmds',
    objects: dhcp_stat_cmds_lib.extract_all_objects(recursive: false),
)
subdir('libloadtests')
subdir('tests')
if HAS_KEA_MSG_COMPILER
    current_source_dir = meson.current_source_dir()
    target_gen_messages = run_target(
        'src-hooks-dhcp-stat_cmds-stat_cmds_messages',
        command: [
            kea_msg_compiler,
            f'@current_source_dir@/stat_cmds_messages.mes',
        ],
    )
    TARGETS_GEN_MESSAGES += [target_gen_messages]
endif
