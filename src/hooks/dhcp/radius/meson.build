configure_file(
    input: 'data/dictionary',
    output: 'dictionary',
    copy: true,
    install: true,
    install_dir: f'@SYSCONFDIR@/kea/radius',
)
dhcp_radius_lib = shared_library(
    'dhcp_radius',
    'cfg_attribute.cc',
    'client_attribute.cc',
    'client_dictionary.cc',
    'client_exchange.cc',
    'client_message.cc',
    'client_server.cc',
    'radius_access.cc',
    'radius_accounting.cc',
    'radius_backend.cc',
    'radius_callout.cc',
    'radius.cc',
    'radius_log.cc',
    'radius_messages.cc',
    'radius_parsers.cc',
    'radius_request.cc',
    'radius_service.cc',
    'radius_utils.cc',
    'version.cc',
    cpp_args: [f'-DDICTIONARY="@PREFIX@/@SYSCONFDIR@/kea/radius/dictionary"'],
    dependencies: [crypto],
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: 'lib/kea/hooks',
    link_with: LIBS_BUILT_SO_FAR,
    name_suffix: 'so',
)
dhcp_radius_archive = static_library(
    'dhcp_radius',
    objects: dhcp_radius_lib.extract_all_objects(recursive: false),
)
subdir('libloadtests')
subdir('tests')
