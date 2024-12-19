kea_exceptions_lib = library('kea-exceptions',
  'exceptions.cc',
  'exceptions.h',
  'isc_assert.h',
  include_directories: [include_directories('.')] + includes,
  install: true,
  install_dir: 'lib',
  link_with: libs_built_so_far,
)
libs_built_so_far = [kea_exceptions_lib] + libs_built_so_far
subdir('tests')
