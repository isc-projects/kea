kea_config_lib = shared_library(
    'kea-config',
    'base_command_mgr.cc',
    'client_connection.cc',
    'cmd_http_listener.cc',
    'cmd_response_creator.cc',
    'command_mgr.cc',
    'config_log.cc',
    'config_messages.cc',
    'hooked_command_mgr.cc',
    'http_command_config.cc',
    'http_command_mgr.cc',
    'http_command_response_creator.cc',
    'unix_command_config.cc',
    'unix_command_mgr.cc',
    dependencies: [CRYPTO_DEP],
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: LIBDIR,
    install_rpath: INSTALL_RPATH,
    build_rpath: BUILD_RPATH,
    link_with: LIBS_BUILT_SO_FAR,
    version: '81.0.0',
    cpp_args: [
        f'-DCONTROL_SOCKET_DIR="@RUNSTATEDIR_INSTALLED@"'
    ],
)
LIBS_BUILT_SO_FAR = [kea_config_lib] + LIBS_BUILT_SO_FAR
subdir('tests')
kea_config_headers = [
    'base_command_mgr.h',
    'client_connection.h',
    'cmd_http_listener.h',
    'cmd_response_creator.h',
    'cmd_response_creator_factory.h',
    'cmds_impl.h',
    'command_mgr.h',
    'config_log.h',
    'config_messages.h',
    'hooked_command_mgr.h',
    'http_command_config.h',
    'http_command_mgr.h',
    'http_command_response_creator.h',
    'http_command_response_creator_factory.h',
    'timeouts.h',
    'unix_command_config.h',
    'unix_command_mgr.h',
]
install_headers(kea_config_headers, preserve_path: true, subdir: 'kea/config')

if KEA_MSG_COMPILER.found()
    current_source_dir = meson.current_source_dir()
    target_gen_messages = run_target(
        'src-lib-config-config_messages',
        command: [
            CD_AND_RUN,
            TOP_SOURCE_DIR,
            KEA_MSG_COMPILER,
            'src/lib/config/config_messages.mes',
        ],
    )
    TARGETS_GEN_MESSAGES += [target_gen_messages]
endif
