sources = [
  'config_base.cc',
  'config_base.h',
  'config_ctl_info.cc',
  'config_ctl_info.h',
  'config_ctl_parser.cc',
  'config_ctl_parser.h',
  'd_cfg_mgr.cc',
  'd_cfg_mgr.h',
  'd_controller.cc',
  'd_controller.h',
  'd_log.cc',
  'd_log.h',
  'd_process.h',
  'daemon.cc',
  'daemon.h',
  'io_service_signal.cc',
  'io_service_signal.h',
  'log_parser.cc',
  'log_parser.h',
  'logging_info.cc',
  'logging_info.h']


process_messages_ch = custom_target('process_messages.[ch]',
                                    output : ['process_messages.cc',
                                              'process_messages.h'],
                                    input : 'process_messages.mes',
                                    command : [kea_msg_compiler, '-d', meson.current_build_dir(), '@INPUT@'])

sources += process_messages_ch

process_lib = static_library('kea-process',
                             sources,
                             cpp_args : ['-DDATA_DIR="' + join_paths(get_option('prefix'), get_option('localstatedir')) + '"'],
                             include_directories : [lib_inc, configuration_inc],
                             install : true)
