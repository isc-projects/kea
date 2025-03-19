kea_log_interprocess_lib = shared_library(
    'kea-log-interprocess',
    'interprocess_sync_file.cc',
    'interprocess_sync_null.cc',
    cpp_args: [f'-DLOCKFILE_DIR="@RUNSTATEDIR_INSTALLED@"'],
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: LIBDIR,
    install_rpath: INSTALL_RPATH,
    build_rpath: BUILD_RPATH,
    link_with: LIBS_BUILT_SO_FAR,
    version: '1.0.0',
)
LIBS_BUILT_SO_FAR = [kea_log_interprocess_lib] + LIBS_BUILT_SO_FAR
subdir('tests')
kea_log_interprocess_headers = [
    'interprocess_sync.h',
    'interprocess_sync_file.h',
    'interprocess_sync_null.h',
]
install_headers(
    kea_log_interprocess_headers,
    preserve_path: true,
    subdir: 'kea/log/interprocess',
)
