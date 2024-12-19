kea_log_interprocess_lib = library('kea-log-interprocess',
  'interprocess_sync.h',
  'interprocess_sync_file.cc',
  'interprocess_sync_file.h',
  'interprocess_sync_null.cc',
  'interprocess_sync_null.h',
  cpp_args: ['-DLOCKFILE_DIR="@0@"'.format(meson.current_build_dir())],
  include_directories: [include_directories('.')] + includes,
  install: true,
  install_dir: 'lib',
  link_with: libs_built_so_far,
)
libs_built_so_far = [kea_log_interprocess_lib] + libs_built_so_far
