sources = [
  'backend_selector.cc',
  'backend_selector.h',
  'database_connection.cc',
  'database_connection.h',
  'dbaccess_parser.h',
  'dbaccess_parser.cc',
  'db_exceptions.h',
  'db_log.cc',
  'db_log.h',
  'server_selector.h']


db_messages_ch = custom_target('db_messages.[ch]',
                               output : ['db_messages.cc',
                                         'db_messages.h'],
                               input : 'db_messages.mes',
                               command : [kea_msg_compiler, '-d', meson.current_build_dir(), '@INPUT@'])

sources += db_messages_ch

database_lib = static_library('kea-database',
                             sources,
                             #cpp_args : ['-DDATA_DIR="' + join_paths(get_option('prefix'), get_option('localstatedir')) + '"'],
                             include_directories : [lib_inc, configuration_inc],
                             install : true)
