if meson.is_cross_build()
    HAS_KEA_MSG_COMPILER = false
    subdir_done()
endif

kea_msg_compiler = executable(
    'kea-msg-compiler',
    'message.cc',
    include_directories: INCLUDES,
    install_dir: 'bin',
    link_with: LIBS_BUILT_SO_FAR,
)
HAS_KEA_MSG_COMPILER = true
