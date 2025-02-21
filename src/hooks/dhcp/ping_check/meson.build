dhcp_ping_check_lib = shared_library(
    'dhcp_ping_check',
    'config_cache.cc',
    'icmp_msg.cc',
    'ping_channel.cc',
    'ping_check_callouts.cc',
    'ping_check_config.cc',
    'ping_check_log.cc',
    'ping_check_messages.cc',
    'ping_check_mgr.cc',
    'ping_context.cc',
    'ping_context_store.cc',
    'version.cc',
    dependencies: [crypto],
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: 'lib/kea/hooks',
    link_with: LIBS_BUILT_SO_FAR,
    name_suffix: 'so',
)
dhcp_ping_check_archive = static_library(
    'dhcp_ping_check',
    objects: dhcp_ping_check_lib.extract_all_objects(recursive: false),
)
subdir('libloadtests')
subdir('tests')

if KEA_MSG_COMPILER.found()
    target_gen_messages = run_target(
        'premium-src-hooks-dhcp-ping_check-ping_check_messages',
        command: [
            CD_AND_RUN,
            TOP_SOURCE_DIR,
            KEA_MSG_COMPILER,
            'src/hooks/dhcp/ping_check/ping_check_messages.mes',
        ],
    )
    TARGETS_GEN_MESSAGES += [target_gen_messages]
endif
