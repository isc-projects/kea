sources = [
  'dhcp_ddns_log.cc',
  'dhcp_ddns_log.h',
  'ncr_io.cc',
  'ncr_io.h',
  'ncr_msg.cc',
  'ncr_msg.h',
  'ncr_udp.cc',
  'ncr_udp.h']

dhcp_ddns_messages_ch = custom_target('dhcp_ddns_messages.[ch]',
                                      output : ['dhcp_ddns_messages.cc',
                                                'dhcp_ddns_messages.h'],
                                      input : 'dhcp_ddns_messages.mes',
                                      command : [kea_msg_compiler, '-d', meson.current_build_dir(), '@INPUT@'])
sources += dhcp_ddns_messages_ch


dhcp_ddns_lib = static_library('kea-dhcp_ddns',
                               sources,
                               include_directories : [lib_inc, configuration_inc],
                               install : true)
