dhcp_limits_lib = shared_library(
    'dhcp_limits',
    'configuration.cc',
    'dhcpv4_callouts.cc',
    'dhcpv6_callouts.cc',
    'limits_logger.cc',
    'limits_messages.cc',
    'limit_manager.cc',
    'load_unload.cc',
    'version.cc',
    dependencies: [crypto],
    include_directories: [include_directories('.'), include_directories('..')] + INCLUDES,
    install: true,
    install_dir: 'lib/kea/hooks',
    link_with: LIBS_BUILT_SO_FAR,
    name_suffix: 'so',
)
dhcp_limits_archive = static_library(
    'dhcp_limits',
    objects: dhcp_limits_lib.extract_all_objects(recursive: false),
)
subdir('libloadtests')
subdir('tests')

if KEA_MSG_COMPILER.found()
    target_gen_messages = run_target(
        'premium-src-hooks-dhcp-limits-limits_messages',
        command: [
            CD_AND_RUN,
            TOP_SOURCE_DIR,
            KEA_MSG_COMPILER,
            'src/hooks/dhcp/limits/limits_messages.mes',
        ],
    )
    TARGETS_GEN_MESSAGES += [target_gen_messages]
endif
