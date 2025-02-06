if not postgresql.found()
    subdir_done()
endif

dhcp_pgsql_lib = shared_library(
    'dhcp_pgsql',
    'pgsql_callouts.cc',
    'pgsql_cb_dhcp4.cc',
    'pgsql_cb_dhcp6.cc',
    'pgsql_cb_impl.cc',
    'pgsql_cb_log.cc',
    'pgsql_cb_messages.cc',
    'pgsql_hb_log.cc',
    'pgsql_hb_messages.cc',
    'pgsql_host_data_source.cc',
    'pgsql_lb_log.cc',
    'pgsql_lb_messages.cc',
    'pgsql_lease_mgr.cc',
    'version.cc',
    dependencies: [crypto, postgresql],
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: 'lib/kea/hooks',
    link_with: LIBS_BUILT_SO_FAR,
    name_suffix: 'so',
)
dhcp_pgsql_archive = static_library(
    'dhcp_pgsql',
    objects: dhcp_pgsql_lib.extract_all_objects(recursive: false),
    link_with: LIBS_BUILT_SO_FAR,
)
subdir('libloadtests')
subdir('tests')
