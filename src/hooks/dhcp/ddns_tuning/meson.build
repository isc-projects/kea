dhcp_ddns_tuning_lib = shared_library(
    'dhcp_ddns_tuning',
    'ddns_tuning.cc',
    'ddns_tuning_callouts.cc',
    'ddns_tuning_log.cc',
    'ddns_tuning_messages.cc',
    'expression_cache.cc',
    'version.cc',
    dependencies: [CRYPTO_DEP],
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: LIBDIR / 'kea/hooks',
    link_with: LIBS_BUILT_SO_FAR,
    name_suffix: 'so',
)
dhcp_ddns_tuning_archive = static_library(
    'dhcp_ddns_tuning',
    objects: dhcp_ddns_tuning_lib.extract_all_objects(recursive: false),
)
subdir('libloadtests')
subdir('tests')

if KEA_MSG_COMPILER.found()
    target_gen_messages = run_target(
        'src-hooks-dhcp-ddns_tuning-ddns_tuning_messages',
        command: [
            CD_AND_RUN,
            TOP_SOURCE_DIR,
            KEA_MSG_COMPILER,
            'src/hooks/dhcp/ddns_tuning/ddns_tuning_messages.mes',
        ],
    )
    TARGETS_GEN_MESSAGES += [target_gen_messages]
endif
