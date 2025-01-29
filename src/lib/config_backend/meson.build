kea_config_backend_lib = library(
    'kea-config_backend',
    'base_config_backend.h',
    'base_config_backend_mgr.h',
    'base_config_backend_pool.h',
    'constants.h',
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: 'lib',
    link_with: LIBS_BUILT_SO_FAR,
)
LIBS_BUILT_SO_FAR = [kea_config_backend_lib] + LIBS_BUILT_SO_FAR
subdir('tests')
