kea_asiodns_lib = library(
    'kea-asiodns',
    'asiodns_messages.cc',
    'io_fetch.cc',
    'logger.cc',
    dependencies: [boost, threads],
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: 'lib',
    link_with: LIBS_BUILT_SO_FAR,
)
LIBS_BUILT_SO_FAR = [kea_asiodns_lib] + LIBS_BUILT_SO_FAR
subdir('tests')
kea_asiodns_headers = ['asiodns_messages.h', 'io_fetch.h', 'logger.h']
install_headers(kea_asiodns_headers, preserve_path: true, subdir: 'kea/asiodns')
