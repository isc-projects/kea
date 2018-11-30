sources = [
  'message.cc']

kea_msg_compiler = executable('kea-msg-compiler',
                              sources,
                              include_directories : [lib_inc, configuration_inc],
                              link_with : [exceptions_lib, log_lib, util_lib],
                              install : true)
