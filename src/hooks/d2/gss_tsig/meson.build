if not KRB5_DEP.found()
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
    dependencies: [KRB5_DEP, CRYPTO_DEP],
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: HOOKS_PATH,
    install_rpath: INSTALL_RPATH,
    build_rpath: BUILD_RPATH,
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

if KEA_MSG_COMPILER.found()
    target_gen_messages = run_target(
        'src-hooks-d2-gss_tsig-gss_tsig_messages',
        command: [
            CD_AND_RUN,
            TOP_SOURCE_DIR,
            KEA_MSG_COMPILER,
            'src/hooks/d2/gss_tsig/gss_tsig_messages.mes',
        ],
    )
    TARGETS_GEN_MESSAGES += [target_gen_messages]
endif
