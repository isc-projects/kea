if not postgresql.found()
  subdir_done()
endif

kea_pgsql_lib = library('kea-pgsql',
  'pgsql_connection.cc',
  'pgsql_connection.h',
  'pgsql_exchange.cc',
  'pgsql_exchange.h',
  cpp_args: [f'-DKEA_ADMIN="@kea_admin@"'],
  dependencies: [postgresql],
  include_directories: [include_directories('.')] + includes,
  install: true,
  install_dir: 'lib',
  link_with: libs_built_so_far,
)
libs_built_so_far += [kea_pgsql_lib]
