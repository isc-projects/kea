if meson.is_cross_build()
    subdir_done()
endif

KEA_MSG_COMPILER = executable(
    'kea-msg-compiler',
    'message.cc',
    include_directories: INCLUDES,
    install: true,
    install_dir: BINDIR,
    link_with: LIBS_BUILT_SO_FAR,
)
