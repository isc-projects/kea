kea_dhcp_ddns_lib = library(
    'kea-dhcp_ddns',
    'dhcp_ddns_log.cc',
    'dhcp_ddns_log.h',
    'dhcp_ddns_messages.cc',
    'dhcp_ddns_messages.h',
    'ncr_io.cc',
    'ncr_io.h',
    'ncr_msg.cc',
    'ncr_msg.h',
    'ncr_udp.cc',
    'ncr_udp.h',
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: 'lib',
    link_with: LIBS_BUILT_SO_FAR,
)
LIBS_BUILT_SO_FAR = [kea_dhcp_ddns_lib] + LIBS_BUILT_SO_FAR
subdir('tests')
