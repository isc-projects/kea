dhcp_rbac_lib = shared_library(
    'dhcp_rbac',
    'rbac.cc',
    'rbac_config.cc',
    'rbac_callouts.cc',
    'rbac_api.cc',
    'rbac_role.cc',
    'rbac_acl.cc',
    'rbac_response_filter.cc',
    'rbac_log.cc',
    'rbac_messages.cc',
    'version.cc',
    dependencies: [CRYPTO_DEP],
    include_directories: HINCLUDES + INCLUDES,
    install: true,
    install_dir: LIBDIR / 'kea/hooks',
    link_with: LIBS_BUILT_SO_FAR,
    name_suffix: 'so',
)
dhcp_rbac_archive = static_library(
    'dhcp_rbac',
    objects: dhcp_rbac_lib.extract_all_objects(recursive: false),
)
subdir('libloadtests')
subdir('tests')

if KEA_MSG_COMPILER.found()
    target_gen_messages = run_target(
        'src-hooks-dhcp-rbac-rbac_messages',
        command: [
            CD_AND_RUN,
            TOP_SOURCE_DIR,
            KEA_MSG_COMPILER,
            'src/hooks/dhcp/rbac/rbac_messages.mes',
        ],
    )
    TARGETS_GEN_MESSAGES += [target_gen_messages]
endif
