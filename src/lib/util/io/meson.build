kea_util_io_lib = shared_library(
    'kea-util-io',
    'fd.cc',
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
    version: '10.0.0',
)
LIBS_BUILT_SO_FAR = [kea_util_io_lib] + LIBS_BUILT_SO_FAR
