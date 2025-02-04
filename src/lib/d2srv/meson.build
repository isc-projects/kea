kea_d2srv_lib = library(
    'kea-d2srv',
    'd2_cfg_mgr.cc',
    'd2_config.cc',
    'd2_log.cc',
    'd2_messages.cc',
    'd2_simple_parser.cc',
    'd2_stats.cc',
    'd2_tsig_key.cc',
    'd2_update_message.cc',
    'd2_zone.cc',
    'dns_client.cc',
    'nc_trans.cc',
    dependencies: [crypto],
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: 'lib',
    link_with: LIBS_BUILT_SO_FAR,
)
LIBS_BUILT_SO_FAR = [kea_d2srv_lib] + LIBS_BUILT_SO_FAR
kea_d2srv_headers = [
    'd2_cfg_mgr.h',
    'd2_config.h',
    'd2_log.h',
    'd2_messages.h',
    'd2_simple_parser.h',
    'd2_stats.h',
    'd2_tsig_key.h',
    'd2_update_message.h',
    'd2_zone.h',
    'dns_client.h',
    'nc_trans.h',
]
install_headers(kea_d2srv_headers, preserve_path: true, subdir: 'kea/d2srv')
