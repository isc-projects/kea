kea_d2srv_lib = shared_library(
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
    dependencies: [CRYPTO_DEP],
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: LIBDIR,
    install_rpath: INSTALL_RPATH,
    build_rpath: BUILD_RPATH,
    link_with: LIBS_BUILT_SO_FAR,
    version: '63.0.0',
)
LIBS_BUILT_SO_FAR = [kea_d2srv_lib] + LIBS_BUILT_SO_FAR
subdir('testutils')
subdir('tests')
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

if KEA_MSG_COMPILER.found()
    current_source_dir = meson.current_source_dir()
    target_gen_messages = run_target(
        'src-lib-d2srv-d2_messages',
        command: [
            CD_AND_RUN,
            TOP_SOURCE_DIR,
            KEA_MSG_COMPILER,
            'src/lib/d2srv/d2_messages.mes',
        ],
    )
    TARGETS_GEN_MESSAGES += [target_gen_messages]
endif
