if not MYSQL_DEP.found()
    subdir_done()
endif

dhcp_mysql_lib = shared_library(
    'dhcp_mysql',
    'mysql_callouts.cc',
    'mysql_cb_dhcp4.cc',
    'mysql_cb_dhcp6.cc',
    'mysql_cb_impl.cc',
    'mysql_cb_log.cc',
    'mysql_cb_messages.cc',
    'mysql_fb_log.cc',
    'mysql_fb_messages.cc',
    'mysql_hb_log.cc',
    'mysql_hb_messages.cc',
    'mysql_host_data_source.cc',
    'mysql_lb_log.cc',
    'mysql_lb_messages.cc',
    'mysql_lease_mgr.cc',
    'mysql_legal_log.cc',
    'version.cc',
    dependencies: [CRYPTO_DEP, MYSQL_DEP],
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: LIBDIR / 'kea/hooks',
    link_with: LIBS_BUILT_SO_FAR,
    name_suffix: 'so',
)
dhcp_mysql_archive = static_library(
    'dhcp_mysql',
    objects: dhcp_mysql_lib.extract_all_objects(recursive: false),
)
subdir('libloadtests')
subdir('tests')

if KEA_MSG_COMPILER.found()
    target_gen_messages = run_target(
        'src-hooks-dhcp-mysql-mysql_cb_messages',
        command: [
            CD_AND_RUN,
            TOP_SOURCE_DIR,
            KEA_MSG_COMPILER,
            'src/hooks/dhcp/mysql/mysql_cb_messages.mes',
        ],
    )
    TARGETS_GEN_MESSAGES += [target_gen_messages]
    target_gen_messages = run_target(
        'src-hooks-dhcp-mysql-mysql_fb_messages',
        command: [
            CD_AND_RUN,
            TOP_SOURCE_DIR,
            KEA_MSG_COMPILER,
            'src/hooks/dhcp/mysql/mysql_fb_messages.mes',
        ],
    )
    TARGETS_GEN_MESSAGES += [target_gen_messages]
    target_gen_messages = run_target(
        'src-hooks-dhcp-mysql-mysql_hb_messages',
        command: [
            CD_AND_RUN,
            TOP_SOURCE_DIR,
            KEA_MSG_COMPILER,
            'src/hooks/dhcp/mysql/mysql_hb_messages.mes',
        ],
    )
    TARGETS_GEN_MESSAGES += [target_gen_messages]
    target_gen_messages = run_target(
        'src-hooks-dhcp-mysql-mysql_lb_messages',
        command: [
            CD_AND_RUN,
            TOP_SOURCE_DIR,
            KEA_MSG_COMPILER,
            'src/hooks/dhcp/mysql/mysql_lb_messages.mes',
        ],
    )
    TARGETS_GEN_MESSAGES += [target_gen_messages]
endif
