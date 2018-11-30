sources = [
  'callout_handle.cc',
  'callout_handle.h',
  'callout_handle_associate.cc',
  'callout_handle_associate.h',
  'callout_manager.cc',
  'callout_manager.h',
  'hooks.h',
  'hooks_log.cc',
  'hooks_log.h',
  'hooks_manager.cc',
  'hooks_manager.h',
  'hooks_config.cc',
  'hooks_config.h',
  'hooks_parser.cc',
  'hooks_parser.h',
  'libinfo.cc',
  'libinfo.h',
  'library_handle.cc',
  'library_handle.h',
  'library_manager.cc',
  'library_manager.h',
  'library_manager_collection.cc',
  'library_manager_collection.h',
  'parking_lots.h',
  'pointer_converter.h',
  'server_hooks.cc',
  'server_hooks.h']


hooks_messages_ch = custom_target('hooks_messages.[ch]',
                                  output : ['hooks_messages.cc',
                                            'hooks_messages.h'],
                                  input : 'hooks_messages.mes',
                                  command : [kea_msg_compiler, '-d', meson.current_build_dir(), '@INPUT@'])

sources += hooks_messages_ch

hooks_lib = static_library('kea-hooks',
                           sources,
                           include_directories : [lib_inc, configuration_inc],
                           install : true)
