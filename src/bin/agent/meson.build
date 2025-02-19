agent_lib = static_library(
    'agent',
    'agent_lexer.cc',
    'agent_parser.cc',
    'ca_cfg_mgr.cc',
    'ca_command_mgr.cc',
    'ca_controller.cc',
    'ca_log.cc',
    'ca_messages.cc',
    'ca_process.cc',
    'ca_response_creator.cc',
    'parser_context.cc',
    'simple_parser.cc',
    dependencies: [crypto],
    include_directories: [include_directories('.')] + INCLUDES,
)
executable(
    'kea-ctrl-agent',
    'main.cc',
    dependencies: [crypto],
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: 'sbin',
    link_with: [agent_lib] + LIBS_BUILT_SO_FAR,
)
subdir('tests')

if HAS_KEA_MSG_COMPILER
    current_source_dir = meson.current_source_dir()
    target_gen_messages = run_target(
        'src-bin-agent-ca_messages',
        command: [kea_msg_compiler, f'@current_source_dir@/ca_messages.mes'],
    )
    TARGETS_GEN_MESSAGES += [target_gen_messages]
endif
