if not NETCONF_DEPS_FOUND
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
    dependencies: NETCONF_DEPS_ARRAY + [crypto],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: [kea_yang_testutils_lib, kea_process_testutils_lib] + LIBS_BUILT_SO_FAR,
    override_options: ['cpp_std=c++20'],
)

executable(
    'kea-netconf',
    'main.cc',
    dependencies: NETCONF_DEPS_ARRAY + [crypto],
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: 'sbin',
    link_with: [netconf_lib] + LIBS_BUILT_SO_FAR,
    override_options: ['cpp_std=c++20'],
)

subdir('tests')

current_source_dir = meson.current_source_dir()
if HAS_KEA_MSG_COMPILER
    target_gen_messages = run_target(
        'src-bin-netconf-netconf_messages',
        command: [
            kea_msg_compiler,
            f'@current_source_dir@/netconf_messages.mes',
        ],
    )
    TARGETS_GEN_MESSAGES += [target_gen_messages]
endif

if flex_exe.found() and bison_exe.found()
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
