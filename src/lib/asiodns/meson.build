kea_asiodns_lib = library(
    'kea-asiodns',
    'asiodns_messages.cc',
    'asiodns_messages.h',
    'io_fetch.cc',
    'io_fetch.h',
    'logger.cc',
    'logger.h',
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: 'lib',
    link_with: LIBS_BUILT_SO_FAR,
)
LIBS_BUILT_SO_FAR = [kea_asiodns_lib] + LIBS_BUILT_SO_FAR
subdir('tests')
