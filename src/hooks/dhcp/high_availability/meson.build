dhcp_ha_lib = shared_library(
    'dhcp_ha',
    'command_creator.cc',
    'communication_state.cc',
    'ha_callouts.cc',
    'ha_config.cc',
    'ha_config_parser.cc',
    'ha_impl.cc',
    'ha_log.cc',
    'ha_messages.cc',
    'ha_service.cc',
    'ha_service_states.cc',
    'lease_sync_filter.cc',
    'lease_update_backlog.cc',
    'query_filter.cc',
    'version.cc',
    dependencies: [CRYPTO_DEP],
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: 'lib/kea/hooks',
    link_with: LIBS_BUILT_SO_FAR,
    name_suffix: 'so',
)
dhcp_ha_archive = static_library(
    'dhcp_ha',
    objects: dhcp_ha_lib.extract_all_objects(recursive: false),
)
subdir('libloadtests')
subdir('tests')

if KEA_MSG_COMPILER.found()
    target_gen_messages = run_target(
        'src-hooks-dhcp-high_availability-ha_messages',
        command: [
            CD_AND_RUN,
            TOP_SOURCE_DIR,
            KEA_MSG_COMPILER,
            'src/hooks/dhcp/high_availability/ha_messages.mes',
        ],
    )
    TARGETS_GEN_MESSAGES += [target_gen_messages]
endif
