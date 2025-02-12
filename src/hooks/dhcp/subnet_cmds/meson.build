dhcp_subnet_cmds_lib = shared_library(
    'dhcp_subnet_cmds',
    'subnet_cmds.cc',
    'subnet_cmds_callouts.cc',
    'subnet_cmds_log.cc',
    'subnet_cmds_messages.cc',
    'version.cc',
    dependencies: [crypto],
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: 'lib/kea/hooks',
    link_with: LIBS_BUILT_SO_FAR,
    name_suffix: 'so',
)
dhcp_subnet_cmds_archive = static_library(
    'dhcp_subnet_cmds',
    objects: dhcp_subnet_cmds_lib.extract_all_objects(recursive: false),
)
subdir('libloadtests')
subdir('tests')
