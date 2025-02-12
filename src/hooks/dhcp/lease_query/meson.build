dhcp_lease_query_lib = shared_library(
    'dhcp_lease_query',
    'blq_service.cc',
    'bulk_lease_query4.cc',
    'bulk_lease_query6.cc',
    'lease_query_callouts.cc',
    'lease_query_connection.cc',
    'lease_query_impl.cc',
    'lease_query_impl4.cc',
    'lease_query_impl6.cc',
    'lease_query_impl_factory.cc',
    'lease_query_log.cc',
    'lease_query_messages.cc',
    'mt_lease_query_mgr.cc',
    'version.cc',
    dependencies: [crypto],
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: 'lib/kea/hooks',
    link_with: LIBS_BUILT_SO_FAR,
    name_suffix: 'so',
)
dhcp_lease_query_archive = static_library(
    'dhcp_lease_query',
    objects: dhcp_lease_query_lib.extract_all_objects(recursive: false),
)
subdir('libloadtests')
subdir('tests')
