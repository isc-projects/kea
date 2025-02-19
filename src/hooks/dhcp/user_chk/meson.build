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

if HAS_KEA_MSG_COMPILER
    current_source_dir = meson.current_source_dir()
    target_gen_messages = run_target(
        'src-hooks-dhcp-user_chk-user_chk_messages',
        command: [
            kea_msg_compiler,
            f'@current_source_dir@/user_chk_messages.mes',
        ],
    )
    TARGETS_GEN_MESSAGES += [target_gen_messages]
endif
