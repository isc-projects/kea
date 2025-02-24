kea_eval_lib = library(
    'kea-eval',
    'dependency.cc',
    'evaluate.cc',
    'eval_context.cc',
    'eval_log.cc',
    'eval_messages.cc',
    'lexer.cc',
    'parser.cc',
    'token.cc',
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: 'lib',
    link_with: LIBS_BUILT_SO_FAR,
)
LIBS_BUILT_SO_FAR = [kea_eval_lib] + LIBS_BUILT_SO_FAR
subdir('tests')
kea_eval_headers = [
    'dependency.h',
    'eval_context.h',
    'eval_context_decl.h',
    'eval_log.h',
    'eval_messages.h',
    'evaluate.h',
    'parser.h',
    'token.h',
]
install_headers(kea_eval_headers, preserve_path: true, subdir: 'kea/eval')

current_source_dir = meson.current_source_dir()
if KEA_MSG_COMPILER.found()
    target_gen_messages = run_target(
        'src-lib-eval-eval_messages',
        command: [
            CD_AND_RUN,
            TOP_SOURCE_DIR,
            KEA_MSG_COMPILER,
            'src/lib/eval/eval_messages.mes',
        ],
    )
    TARGETS_GEN_MESSAGES += [target_gen_messages]
endif

if FLEX.found() and BISON.found()
    target_parser = run_target(
        'src-lib-eval-parser',
        command: [
            CD_AND_RUN,
            current_source_dir,
            BISON,
            '-Wno-yacc',
            '--defines=parser.h',
            '-o',
            'parser.cc',
            'parser.yy',
        ],
    )
    target_lexer = run_target(
        'src-lib-eval-lexer',
        command: [
            CD_AND_RUN,
            current_source_dir,
            FLEX,
            '--prefix',
            'eval',
            '-o',
            'lexer.cc',
            'lexer.ll',
        ],
    )
    TARGETS_GEN_PARSER += [target_parser, target_lexer]
endif
