dhcp_bootp_lib = shared_library(
    'dhcp_bootp',
    'bootp_callouts.cc',
    'bootp_log.cc',
    'bootp_messages.cc',
    'version.cc',
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: 'lib/kea/hooks',
    link_with: LIBS_BUILT_SO_FAR,
    name_suffix: 'so',
)
dhcp_bootp_archive = static_library(
    'dhcp_bootp',
    objects: dhcp_bootp_lib.extract_all_objects(recursive: false),
)
subdir('libloadtests')
subdir('tests')
