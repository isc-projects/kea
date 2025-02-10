lfc_lib = static_library(
    'lfc',
    'lfc_controller.cc',
    'lfc_log.cc',
    'lfc_messages.cc',
    include_directories: [include_directories('.')] + INCLUDES,
)
executable(
    'kea-lfc',
    'main.cc',
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: 'sbin',
    link_with: [lfc_lib] + LIBS_BUILT_SO_FAR,
)
subdir('tests')
