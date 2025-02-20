lfc_lib = static_library(
    'lfc',
    'lfc_controller.cc',
    'lfc_log.cc',
    'lfc_messages.cc',
    include_directories: [include_directories('.')] + INCLUDES,
)
executable(
    'kea-lfc',
    'main.cc',
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: 'sbin',
    link_with: [lfc_lib] + LIBS_BUILT_SO_FAR,
)
subdir('tests')

if HAS_KEA_MSG_COMPILER
    target_gen_messages = run_target(
        'src-bin-lfc-lfc_messages',
        command: [
            CD_AND_RUN,
            TOP_SOURCE_DIR,
            KEA_MSG_COMPILER,
            'src/bin/lfc/lfc_messages.mes',
        ],
    )
    TARGETS_GEN_MESSAGES += [target_gen_messages]
endif
