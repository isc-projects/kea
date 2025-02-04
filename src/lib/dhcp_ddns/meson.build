kea_dhcp_ddns_lib = library(
    'kea-dhcp_ddns',
    'dhcp_ddns_log.cc',
    'dhcp_ddns_messages.cc',
    'ncr_io.cc',
    'ncr_msg.cc',
    'ncr_udp.cc',
    dependencies: [boost],
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: 'lib',
    link_with: LIBS_BUILT_SO_FAR,
)
LIBS_BUILT_SO_FAR = [kea_dhcp_ddns_lib] + LIBS_BUILT_SO_FAR
subdir('tests')
kea_dhcp_ddns_headers = [
    'dhcp_ddns_log.h',
    'dhcp_ddns_messages.h',
    'ncr_io.h',
    'ncr_msg.h',
    'ncr_udp.h',
]
install_headers(
    kea_dhcp_ddns_headers,
    preserve_path: true,
    subdir: 'kea/dhcp_ddns',
)
