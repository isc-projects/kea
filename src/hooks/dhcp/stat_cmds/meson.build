dhcp_stat_cmds_lib = library(
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
