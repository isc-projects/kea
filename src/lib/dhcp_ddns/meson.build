kea_dhcp_ddns_lib = shared_library(
    'kea-dhcp_ddns',
    'dhcp_ddns_log.cc',
    'dhcp_ddns_messages.cc',
    'ncr_io.cc',
    'ncr_msg.cc',
    'ncr_udp.cc',
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: LIBDIR,
    install_rpath: INSTALL_RPATH,
    build_rpath: BUILD_RPATH,
    link_with: LIBS_BUILT_SO_FAR,
    version: '78.0.0',
)
LIBS_BUILT_SO_FAR = [kea_dhcp_ddns_lib] + LIBS_BUILT_SO_FAR
subdir('tests')
kea_dhcp_ddns_headers = [
    'dhcp_ddns_log.h',
    'dhcp_ddns_messages.h',
    'ncr_io.h',
    'ncr_msg.h',
    'ncr_udp.h',
]
install_headers(
    kea_dhcp_ddns_headers,
    preserve_path: true,
    subdir: 'kea/dhcp_ddns',
)

if KEA_MSG_COMPILER.found()
    current_source_dir = meson.current_source_dir()
    target_gen_messages = run_target(
        'src-lib-dhcp_ddns-dhcp_ddns_messages',
        command: [
            CD_AND_RUN,
            TOP_SOURCE_DIR,
            KEA_MSG_COMPILER,
            'src/lib/dhcp_ddns/dhcp_ddns_messages.mes',
        ],
    )
    TARGETS_GEN_MESSAGES += [target_gen_messages]
endif
