sources = [
  'data.cc',
  'data.h',
  'cfg_to_element.h',
  'dhcp_config_error.h',
  'command_interpreter.cc',
  'command_interpreter.h',
  'json_feed.cc',
  'json_feed.h',
  'simple_parser.cc',
  'simple_parser.h',
  'stamped_element.cc',
  'stamped_element.h',
  'stamped_value.cc',
  'stamped_value.h',
  'user_context.cc',
  'user_context.h']


cc_lib = static_library('kea-cc',
                        sources,
                        include_directories : [lib_inc, configuration_inc],
                        install : true)
