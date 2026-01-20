configure_file(
    input: 'data/dictionary',
    output: 'dictionary',
    copy: true,
    install: true,
    install_dir: SYSCONFDIR / 'kea/radius',
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
    'radius_status.cc',
    'radius_tls.cc',
    'radius_utils.cc',
    'version.cc',
    cpp_args: [f'-DDICTIONARY="@SYSCONFDIR_INSTALLED@/kea/radius/dictionary"'],
    dependencies: [CRYPTO_DEP],
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: HOOKS_PATH,
    install_rpath: INSTALL_RPATH,
    build_rpath: BUILD_RPATH,
    link_with: LIBS_BUILT_SO_FAR,
    name_suffix: 'so',
)
dhcp_radius_archive = static_library(
    'dhcp_radius',
    objects: dhcp_radius_lib.extract_all_objects(recursive: false),
)
subdir('libloadtests')
subdir('tests')

if KEA_MSG_COMPILER.found()
    target_gen_messages = run_target(
        'src-hooks-dhcp-radius-radius_messages',
        command: [
            CD_AND_RUN,
            TOP_SOURCE_DIR,
            KEA_MSG_COMPILER,
            'src/hooks/dhcp/radius/radius_messages.mes',
        ],
    )
    TARGETS_GEN_MESSAGES += [target_gen_messages]
endif
