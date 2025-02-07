# Not install it
dhcp_user_chk_lib = shared_library(
    'dhcp_user_chk',
    'load_unload.cc',
    'pkt_receive_co.cc',
    'pkt_send_co.cc',
    'subnet_select_co.cc',
    'user.cc',
    'user_chk_log.cc',
    'user_chk_messages.cc',
    'user_file.cc',
    'user_registry.cc',
    'version.cc',
    dependencies: [boost],
    include_directories: [include_directories('.')] + INCLUDES,
    install: false,
    install_dir: 'lib/kea/hooks',
    link_with: LIBS_BUILT_SO_FAR,
    name_suffix: 'so',
)
dhcp_user_chk_archive = static_library(
    'dhcp_user_chk',
    objects: dhcp_user_chk_lib.extract_all_objects(recursive: false),
)
subdir('tests')
