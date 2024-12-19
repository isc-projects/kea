kea_cfgrpt_lib = library('kea-cfgrpt',
  'cfgrpt.cc',
  'config_report.cc',
  'config_report.h',
  include_directories: [include_directories('.')] + includes,
  install: true,
  install_dir: 'lib',
  link_with: libs_built_so_far,
)
libs_built_so_far = [kea_cfgrpt_lib] + libs_built_so_far
