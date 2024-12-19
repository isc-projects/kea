kea_asiodns_lib = library('kea-asiodns',
  'asiodns_messages.cc',
  'asiodns_messages.h',
  'io_fetch.cc',
  'io_fetch.h',
  'logger.cc',
  'logger.h',
  include_directories: [include_directories('.')] + includes,
  install: true,
  install_dir: 'lib',
  link_with: libs_built_so_far,
)
libs_built_so_far = [kea_asiodns_lib] + libs_built_so_far
subdir('tests')
