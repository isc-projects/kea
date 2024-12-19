if not mysql.found()
  subdir_done()
endif

kea_mysql_lib = library('kea-mysql',
  'mysql_binding.cc',
  'mysql_binding.h',
  'mysql_connection.cc',
  'mysql_connection.h',
  'mysql_constants.h',
  cpp_args: [f'-DKEA_ADMIN="@kea_admin@"'],
  dependencies: [mysql],
  include_directories: [include_directories('.')] + includes,
  install: true,
  install_dir: 'lib',
  link_with: libs_built_so_far,
)
libs_built_so_far += [kea_mysql_lib]
