dhcp_flex_option_lib = shared_library(
    'dhcp_flex_option',
    'flex_option.cc',
    'flex_option_callouts.cc',
    'flex_option_log.cc',
    'flex_option_messages.cc',
    'version.cc',
    dependencies: [CRYPTO_DEP],
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: 'lib/kea/hooks',
    link_with: LIBS_BUILT_SO_FAR,
    name_suffix: 'so',
)
dhcp_flex_option_archive = static_library(
    'dhcp_flex_option',
    objects: dhcp_flex_option_lib.extract_all_objects(recursive: false),
)
subdir('libloadtests')
subdir('tests')

if KEA_MSG_COMPILER.found()
    target_gen_messages = run_target(
        'src-hooks-dhcp-flex_option-flex_option_messages',
        command: [
            CD_AND_RUN,
            TOP_SOURCE_DIR,
            KEA_MSG_COMPILER,
            'src/hooks/dhcp/flex_option/flex_option_messages.mes',
        ],
    )
    TARGETS_GEN_MESSAGES += [target_gen_messages]
endif
