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
    dependencies: [CRYPTO_DEP],
    include_directories: [include_directories('.')] + INCLUDES,
)
kea_dhcp4 = executable(
    'kea-dhcp4',
    'main.cc',
    dependencies: [CRYPTO_DEP],
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: 'sbin',
    link_with: [dhcp4_lib] + LIBS_BUILT_SO_FAR,
)
subdir('tests')

current_source_dir = meson.current_source_dir()
if KEA_MSG_COMPILER.found()
    target_gen_messages = run_target(
        'src-bin-dhcp4-dhcp4_messages',
        command: [
            CD_AND_RUN,
            TOP_SOURCE_DIR,
            KEA_MSG_COMPILER,
            'src/bin/dhcp4/dhcp4_messages.mes',
        ],
    )
    TARGETS_GEN_MESSAGES += [target_gen_messages]
endif

if FLEX.found() and BISON.found()
    target_parser = run_target(
        'src-bin-dhcp4-parser',
        command: [
            CD_AND_RUN,
            current_source_dir,
            BISON,
            '-Wno-yacc',
            '--defines=dhcp4_parser.h',
            '--report=all',
            '--report-file=dhcp4_parser.report',
            '-o',
            'dhcp4_parser.cc',
            'dhcp4_parser.yy',
        ],
    )
    target_lexer = run_target(
        'src-bin-dhcp4-lexer',
        command: [
            CD_AND_RUN,
            current_source_dir,
            FLEX,
            '--prefix',
            'parser4_',
            '-o',
            'dhcp4_lexer.cc',
            'dhcp4_lexer.ll',
        ],
    )
    TARGETS_GEN_PARSER += [target_parser, target_lexer]
endif
