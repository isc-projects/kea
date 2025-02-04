dhcp_bootp_lib = library(
    'dhcp_bootp',
    'bootp_callouts.cc',
    'bootp_log.cc',
    'bootp_messages.cc',
    'version.cc',
    dependencies: [boost],
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: 'lib/kea/hooks',
    link_with: LIBS_BUILT_SO_FAR,
    name_suffix: 'so',
)
