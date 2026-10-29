dhcp_cb_cmds_lib = shared_library(
    'dhcp_cb_cmds',
    'cb_cmds_callouts.cc',
    'cb_cmds_dhcp4.cc',
    'cb_cmds_dhcp6.cc',
    'cb_cmds_impl.cc',
    'cb_cmds_log.cc',
    'cb_cmds_messages.cc',
    'cb_parsers.cc',
    'version.cc',
    dependencies: [CRYPTO_DEP],
    include_directories: HINCLUDES + INCLUDES,
    install: true,
    install_dir: LIBDIR / 'kea/hooks',
    link_with: LIBS_BUILT_SO_FAR,
    name_suffix: 'so',
)
dhcp_cb_cmds_archive = static_library(
    'dhcp_cb_cmds',
    objects: dhcp_cb_cmds_lib.extract_all_objects(recursive: false),
)
subdir('libloadtests')
subdir('tests')

if KEA_MSG_COMPILER.found()
    target_gen_messages = run_target(
        'src-hooks-dhcp-cb_cmds-cb_cmds_messages',
        command: [
            CD_AND_RUN,
            TOP_SOURCE_DIR,
            KEA_MSG_COMPILER,
            'src/hooks/dhcp/cb_cmds/cb_cmds_messages.mes',
        ],
    )
    TARGETS_GEN_MESSAGES += [target_gen_messages]
endif
