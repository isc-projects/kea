kea_exceptions_lib = library(
    'kea-exceptions',
    'exceptions.cc',
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: 'lib',
    link_with: LIBS_BUILT_SO_FAR,
)
LIBS_BUILT_SO_FAR = [kea_exceptions_lib] + LIBS_BUILT_SO_FAR
subdir('tests')
kea_exceptions_headers = ['exceptions.h', 'isc_assert.h']
install_headers(
    kea_exceptions_headers,
    preserve_path: true,
    subdir: 'kea/exceptions',
)
