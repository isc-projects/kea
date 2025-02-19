dhcp4_lib = static_library(
    'dhcp4',
    'client_handler.cc',
    'ctrl_dhcp4_srv.cc',
    'dhcp4to6_ipc.cc',
    'dhcp4_lexer.cc',
    'dhcp4_log.cc',
    'dhcp4_messages.cc',
    'dhcp4_parser.cc',
    'dhcp4_srv.cc',
    'json_config_parser.cc',
    'parser_context.cc',
    dependencies: [crypto],
    include_directories: [include_directories('.')] + INCLUDES,
)
executable(
    'kea-dhcp4',
    'main.cc',
    dependencies: [crypto],
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: 'sbin',
    link_with: [dhcp4_lib] + LIBS_BUILT_SO_FAR,
)
subdir('tests')

if HAS_KEA_MSG_COMPILER
    current_source_dir = meson.current_source_dir()
    target_gen_messages = run_target(
        'src-bin-dhcp4-dhcp4_messages',
        command: [kea_msg_compiler, f'@current_source_dir@/dhcp4_messages.mes'],
    )
    TARGETS_GEN_MESSAGES += [target_gen_messages]
endif
