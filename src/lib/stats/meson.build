kea_stats_lib = library(
    'kea-stats',
    'context.cc',
    'context.h',
    'observation.cc',
    'observation.h',
    'stats_mgr.cc',
    'stats_mgr.h',
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: 'lib',
    link_with: LIBS_BUILT_SO_FAR,
)
LIBS_BUILT_SO_FAR = [kea_stats_lib] + LIBS_BUILT_SO_FAR
subdir('tests')
