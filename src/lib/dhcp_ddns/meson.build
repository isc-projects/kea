kea_dhcp_ddns_lib = library('kea-dhcp_ddns',
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
  include_directories: [include_directories('.')] + includes,
  install: true,
  install_dir: 'lib',
  link_with: libs_built_so_far,
)
libs_built_so_far = [kea_dhcp_ddns_lib] + libs_built_so_far
subdir('tests')
