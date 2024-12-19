kea_config_backend_lib = library('kea-config_backend',
  'base_config_backend.h',
  'base_config_backend_mgr.h',
  'base_config_backend_pool.h',
  'constants.h',
  include_directories: [include_directories('.')] + includes,
  install: true,
  install_dir: 'lib',
  link_with: libs_built_so_far,
)
libs_built_so_far = [kea_config_backend_lib] + libs_built_so_far
subdir('tests')
