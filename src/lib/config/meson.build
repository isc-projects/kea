sources = [
  'cmds_impl.h',
  'base_command_mgr.cc',
  'base_command_mgr.h',
  'client_connection.cc',
  'client_connection.h',
  'command_mgr.cc',
  'command_mgr.h',
  'config_log.h',
  'config_log.cc',
  'hooked_command_mgr.cc',
  'hooked_command_mgr.h',
  'timeouts.h']


config_messages_ch = custom_target('config_messages.[ch]',
                                   output : ['config_messages.cc',
                                             'config_messages.h'],
                                   input : 'config_messages.mes',
                                   command : [kea_msg_compiler, '-d', meson.current_build_dir(), '@INPUT@'])

sources += config_messages_ch

cfgclient_lib = static_library('kea-cfgclient',
                               sources,
                               include_directories : [lib_inc, configuration_inc],
                               install : true)
