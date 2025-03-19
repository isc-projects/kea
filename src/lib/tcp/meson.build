kea_tcp_lib = shared_library(
    'kea-tcp',
    'mt_tcp_listener_mgr.cc',
    'tcp_connection.cc',
    'tcp_connection_pool.cc',
    'tcp_listener.cc',
    'tcp_log.cc',
    'tcp_messages.cc',
    'tcp_stream_msg.cc',
    dependencies: [CRYPTO_DEP],
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: LIBDIR,
    install_rpath: INSTALL_RPATH,
    build_rpath: BUILD_RPATH,
    link_with: LIBS_BUILT_SO_FAR,
    version: '31.0.0',
)
LIBS_BUILT_SO_FAR = [kea_tcp_lib] + LIBS_BUILT_SO_FAR
subdir('tests')
kea_tcp_headers = [
    'mt_tcp_listener_mgr.h',
    'tcp_connection.h',
    'tcp_connection_acceptor.h',
    'tcp_connection_pool.h',
    'tcp_listener.h',
    'tcp_log.h',
    'tcp_messages.h',
    'tcp_stream_msg.h',
]
install_headers(kea_tcp_headers, preserve_path: true, subdir: 'kea/tcp')

if KEA_MSG_COMPILER.found()
    current_source_dir = meson.current_source_dir()
    target_gen_messages = run_target(
        'src-lib-tcp-tcp_messages',
        command: [
            CD_AND_RUN,
            TOP_SOURCE_DIR,
            KEA_MSG_COMPILER,
            'src/lib/tcp/tcp_messages.mes',
        ],
    )
    TARGETS_GEN_MESSAGES += [target_gen_messages]
endif
