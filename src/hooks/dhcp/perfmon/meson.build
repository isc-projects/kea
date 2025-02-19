dhcp_perfmon_lib = shared_library(
    'dhcp_perfmon',
    'alarm.cc',
    'alarm_store.cc',
    'monitored_duration.cc',
    'monitored_duration_store.cc',
    'perfmon_callouts.cc',
    'perfmon_config.cc',
    'perfmon_log.cc',
    'perfmon_messages.cc',
    'perfmon_mgr.cc',
    'version.cc',
    dependencies: [crypto],
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: 'lib/kea/hooks',
    link_with: LIBS_BUILT_SO_FAR,
    name_suffix: 'so',
)
dhcp_perfmon_archive = static_library(
    'dhcp_perfmon',
    objects: dhcp_perfmon_lib.extract_all_objects(recursive: false),
)
subdir('libloadtests')
subdir('tests')

if HAS_KEA_MSG_COMPILER
    current_source_dir = meson.current_source_dir()
    target_gen_messages = run_target(
        'src-hooks-dhcp-perfmon-perfmon_messages',
        command: [
            kea_msg_compiler,
            f'@current_source_dir@/perfmon_messages.mes',
        ],
    )
    TARGETS_GEN_MESSAGES += [target_gen_messages]
endif
