kea_stats_lib = library('kea-stats',
  'context.cc',
  'context.h',
  'observation.cc',
  'observation.h',
  'stats_mgr.cc',
  'stats_mgr.h',
  include_directories: [include_directories('.')] + includes,
  install: true,
  install_dir: 'lib',
  link_with: libs_built_so_far,
)
libs_built_so_far = [kea_stats_lib] + libs_built_so_far
subdir('tests')
