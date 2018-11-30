sources = [
  'mysql_connection.cc',
  'mysql_connection.h',
  'mysql_binding.cc',
  'mysql_binding.h',
  'mysql_constants.h']

mysql_dep = dependency('mysqlclient')

foolib = static_library('kea-mysql',
                        sources,
                        include_directories : [lib_inc, configuration_inc],
                        dependencies : mysql_dep,
                        install : true)
