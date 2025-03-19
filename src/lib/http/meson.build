kea_http_lib = shared_library(
    'kea-http',
    'auth_log.cc',
    'auth_messages.cc',
    'basic_auth.cc',
    'basic_auth_config.cc',
    'cfg_http_header.cc',
    'client.cc',
    'connection.cc',
    'connection_pool.cc',
    'date_time.cc',
    'http_header.cc',
    'http_log.cc',
    'http_message.cc',
    'http_messages.cc',
    'http_message_parser_base.cc',
    'listener.cc',
    'listener_impl.cc',
    'post_request.cc',
    'post_request_json.cc',
    'request.cc',
    'request_parser.cc',
    'response.cc',
    'response_creator.cc',
    'response_json.cc',
    'response_parser.cc',
    'url.cc',
    dependencies: [CRYPTO_DEP],
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: LIBDIR,
    install_rpath: INSTALL_RPATH,
    build_rpath: BUILD_RPATH,
    link_with: LIBS_BUILT_SO_FAR,
    version: '85.0.0',
)
LIBS_BUILT_SO_FAR = [kea_http_lib] + LIBS_BUILT_SO_FAR
subdir('tests')
kea_http_headers = [
    'auth_config.h',
    'auth_log.h',
    'auth_messages.h',
    'basic_auth.h',
    'basic_auth_config.h',
    'cfg_http_header.h',
    'client.h',
    'connection.h',
    'connection_pool.h',
    'date_time.h',
    'header_context.h',
    'http_acceptor.h',
    'http_header.h',
    'http_log.h',
    'http_message.h',
    'http_message_parser_base.h',
    'http_messages.h',
    'http_types.h',
    'listener.h',
    'listener_impl.h',
    'post_request.h',
    'post_request_json.h',
    'request.h',
    'request_context.h',
    'request_parser.h',
    'response.h',
    'response_context.h',
    'response_creator.h',
    'response_creator_factory.h',
    'response_json.h',
    'response_parser.h',
    'url.h',
]
install_headers(kea_http_headers, preserve_path: true, subdir: 'kea/http')

if KEA_MSG_COMPILER.found()
    current_source_dir = meson.current_source_dir()
    target_gen_messages = run_target(
        'src-lib-http-auth_messages',
        command: [
            CD_AND_RUN,
            TOP_SOURCE_DIR,
            KEA_MSG_COMPILER,
            'src/lib/http/auth_messages.mes',
        ],
    )
    TARGETS_GEN_MESSAGES += [target_gen_messages]
    target_gen_messages = run_target(
        'src-lib-http-http_messages',
        command: [
            CD_AND_RUN,
            TOP_SOURCE_DIR,
            KEA_MSG_COMPILER,
            'src/lib/http/http_messages.mes',
        ],
    )
    TARGETS_GEN_MESSAGES += [target_gen_messages]
endif
