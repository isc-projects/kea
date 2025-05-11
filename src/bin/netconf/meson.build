if not NETCONF_DEP.found()
    subdir_done()
endif

netconf_lib = static_library(
    'netconf',
    'control_socket.cc',
    'http_control_socket.cc',
    'netconf.cc',
    'netconf_cfg_mgr.cc',
    'netconf_config.cc',
    'netconf_controller.cc',
    'netconf_lexer.cc',
    'netconf_log.cc',
    'netconf_messages.cc',
    'netconf_parser.cc',
    'netconf_process.cc',
    'parser_context.cc',
    'simple_parser.cc',
    'stdout_control_socket.cc',
    'unix_control_socket.cc',
    dependencies: [NETCONF_DEP, CRYPTO_DEP],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
)

executable(
    'kea-netconf',
    'main.cc',
    dependencies: [NETCONF_DEP, CRYPTO_DEP],
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: SBINDIR,
    install_rpath: INSTALL_RPATH,
    build_rpath: BUILD_RPATH,
    link_with: [netconf_lib] + LIBS_BUILT_SO_FAR,
)

subdir('tests')

current_source_dir = meson.current_source_dir()
if KEA_MSG_COMPILER.found()
    target_gen_messages = run_target(
        'src-bin-netconf-netconf_messages',
        command: [
            CD_AND_RUN,
            TOP_SOURCE_DIR,
            KEA_MSG_COMPILER,
            'src/bin/netconf/netconf_messages.mes',
        ],
    )
    TARGETS_GEN_MESSAGES += [target_gen_messages]
endif

if FLEX.found() and BISON.found()
    target_parser = run_target(
        'src-bin-netconf-parser',
        command: [
            CD_AND_RUN,
            current_source_dir,
            BISON,
            '-Wno-yacc',
            '--defines=netconf_parser.h',
            '--report=all',
            '--report-file=netconf_parser.report',
            '-o',
            'netconf_parser.cc',
            'netconf_parser.yy',
        ],
    )
    target_lexer = run_target(
        'src-bin-netconf-lexer',
        command: [
            CD_AND_RUN,
            current_source_dir,
            FLEX,
            '--prefix',
            'netconf_',
            '-o',
            'netconf_lexer.cc',
            'netconf_lexer.ll',
        ],
    )
    TARGETS_GEN_PARSER += [target_parser, target_lexer]
endif
