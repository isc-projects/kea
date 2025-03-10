d2_lib = static_library(
    'd2',
    'check_exists_add.cc',
    'check_exists_remove.cc',
    'd2_controller.cc',
    'd2_lexer.cc',
    'd2_parser.cc',
    'd2_process.cc',
    'd2_queue_mgr.cc',
    'd2_update_mgr.cc',
    'nc_add.cc',
    'nc_remove.cc',
    'parser_context.cc',
    'simple_add.cc',
    'simple_add_without_dhcid.cc',
    'simple_remove.cc',
    'simple_remove_without_dhcid.cc',
    dependencies: [CRYPTO_DEP],
    include_directories: [include_directories('.')] + INCLUDES,
)
executable(
    'kea-dhcp-ddns',
    'main.cc',
    dependencies: [CRYPTO_DEP],
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: 'sbin',
    link_with: [d2_lib] + LIBS_BUILT_SO_FAR,
)
subdir('tests')

if FLEX.found() and BISON.found()
    current_source_dir = meson.current_source_dir()
    target_parser = run_target(
        'src-bin-d2-parser',
        command: [
            CD_AND_RUN,
            current_source_dir,
            BISON,
            '-Wno-yacc',
            '--defines=d2_parser.h',
            '--report=all',
            '--report-file=d2_parser.report',
            '-o',
            'd2_parser.cc',
            'd2_parser.yy',
        ],
    )
    target_lexer = run_target(
        'src-bin-d2-lexer',
        command: [
            CD_AND_RUN,
            current_source_dir,
            FLEX,
            '--prefix',
            'd2_parser_',
            '-o',
            'd2_lexer.cc',
            'd2_lexer.ll',
        ],
    )
    TARGETS_GEN_PARSER += [target_parser, target_lexer]
endif
