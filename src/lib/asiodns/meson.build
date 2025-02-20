kea_asiodns_lib = library(
    'kea-asiodns',
    'asiodns_messages.cc',
    'io_fetch.cc',
    'logger.cc',
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: 'lib',
    link_with: LIBS_BUILT_SO_FAR,
)
LIBS_BUILT_SO_FAR = [kea_asiodns_lib] + LIBS_BUILT_SO_FAR
subdir('tests')
kea_asiodns_headers = ['asiodns_messages.h', 'io_fetch.h', 'logger.h']
install_headers(kea_asiodns_headers, preserve_path: true, subdir: 'kea/asiodns')

if HAS_KEA_MSG_COMPILER
    current_source_dir = meson.current_source_dir()
    target_gen_messages = run_target(
        'src-lib-asiodns-asiodns_messages',
        command: [
            CD_AND_RUN,
            TOP_SOURCE_DIR,
            KEA_MSG_COMPILER,
            'src/lib/asiodns/asiodns_messages.mes',
        ],
    )
    TARGETS_GEN_MESSAGES += [target_gen_messages]
endif
