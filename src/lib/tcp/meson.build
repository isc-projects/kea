kea_tcp_lib = library(
    'kea-tcp',
    'mt_tcp_listener_mgr.cc',
    'tcp_connection.cc',
    'tcp_connection_pool.cc',
    'tcp_listener.cc',
    'tcp_log.cc',
    'tcp_messages.cc',
    'tcp_stream_msg.cc',
    dependencies: [crypto],
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: 'lib',
    link_with: LIBS_BUILT_SO_FAR,
)
LIBS_BUILT_SO_FAR = [kea_tcp_lib] + LIBS_BUILT_SO_FAR
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
