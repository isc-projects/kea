lfc_lib = static_library(
    'lfc',
    'lfc_controller.cc',
    'lfc_controller.h',
    'lfc_log.cc',
    'lfc_log.h',
    'lfc_messages.cc',
    'lfc_messages.h',
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
)
executable(
    'kea-lfc',
    'main.cc',
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: 'sbin',
    link_with: LIBS_BUILT_SO_FAR + [lfc_lib],
)
