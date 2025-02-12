dhcp_ddns_tuning_lib = shared_library(
    'dhcp_ddns_tuning',
    'ddns_tuning.cc',
    'ddns_tuning_callouts.cc',
    'ddns_tuning_log.cc',
    'ddns_tuning_messages.cc',
    'expression_cache.cc',
    'version.cc',
    dependencies: [crypto],
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: 'lib/kea/hooks',
    link_with: LIBS_BUILT_SO_FAR,
    name_suffix: 'so',
)
dhcp_ddns_tuning_archive = static_library(
    'dhcp_ddns_tuning',
    objects: dhcp_ddns_tuning_lib.extract_all_objects(recursive: false),
)
subdir('libloadtests')
subdir('tests')
