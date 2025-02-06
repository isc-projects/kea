dhcp_flex_option_lib = shared_library(
    'dhcp_flex_option',
    'flex_option.cc',
    'flex_option_callouts.cc',
    'flex_option_log.cc',
    'flex_option_messages.cc',
    'version.cc',
    dependencies: [crypto],
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: 'lib/kea/hooks',
    link_with: LIBS_BUILT_SO_FAR,
    name_suffix: 'so',
)
dhcp_flex_option_archive = static_library(
    'dhcp_flex_option',
    objects: dhcp_flex_option_lib.extract_all_objects(recursive: false),
    link_with: LIBS_BUILT_SO_FAR,
)
subdir('libloadtests')
subdir('tests')
