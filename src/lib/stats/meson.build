kea_stats_lib = shared_library(
    'kea-stats',
    'context.cc',
    'observation.cc',
    'stats_mgr.cc',
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: LIBDIR,
    link_with: LIBS_BUILT_SO_FAR,
    version: '51.0.0',
)
LIBS_BUILT_SO_FAR = [kea_stats_lib] + LIBS_BUILT_SO_FAR
subdir('tests')
kea_stats_headers = ['context.h', 'observation.h', 'stats_mgr.h']
install_headers(kea_stats_headers, preserve_path: true, subdir: 'kea/stats')
