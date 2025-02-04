dhcp_flex_option_lib = library(
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
