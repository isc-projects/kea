if not mysql.found()
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
    'mysql_hb_log.cc',
    'mysql_hb_messages.cc',
    'mysql_host_data_source.cc',
    'mysql_lb_log.cc',
    'mysql_lb_messages.cc',
    'mysql_lease_mgr.cc',
    'version.cc',
    dependencies: [crypto, mysql],
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: 'lib/kea/hooks',
    link_with: LIBS_BUILT_SO_FAR,
    name_suffix: 'so',
)
dhcp_mysql_archive = static_library(
    'dhcp_mysql',
    objects: dhcp_mysql_lib.extract_all_objects(recursive: false),
    link_with: LIBS_BUILT_SO_FAR,
)
subdir('libloadtests')
subdir('tests')
