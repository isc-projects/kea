if not krb5.found()
    subdir_done()
endif

ddns_gss_tsig_lib = shared_library(
    'ddns_gss_tsig',
    'gss_tsig_api.cc',
    'gss_tsig_callouts.cc',
    'gss_tsig_cfg.cc',
    'gss_tsig_context.cc',
    'gss_tsig_impl.cc',
    'gss_tsig_key.cc',
    'gss_tsig_log.cc',
    'gss_tsig_messages.cc',
    'managed_key.cc',
    'tkey_exchange.cc',
    'version.cc',
    dependencies: [krb5, crypto],
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: 'lib/kea/hooks',
    link_with: LIBS_BUILT_SO_FAR,
    name_suffix: 'so',
)
ddns_gss_tsig_archive = static_library(
    'ddns_gss_tsig',
    objects: ddns_gss_tsig_lib.extract_all_objects(recursive: false),
)
subdir('testutils')
subdir('libloadtests')
subdir('tests')
