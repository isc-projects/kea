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
