dhcp_flex_id_lib = shared_library(
    'dhcp_flex_id',
    'callouts.cc',
    'flex_id_log.cc',
    'flex_id_messages.cc',
    'load_unload.cc',
    'version.cc',
    dependencies: [crypto],
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: 'lib/kea/hooks',
    link_with: LIBS_BUILT_SO_FAR,
    name_suffix: 'so',
)
dhcp_flex_id_archive = static_library(
    'dhcp_flex_id',
    objects: dhcp_flex_id_lib.extract_all_objects(recursive: false),
)
subdir('libloadtests')
subdir('tests')
