dhcp_host_cache_lib = shared_library(
    'dhcp_host_cache',
    'entry.cc',
    'host_cache.cc',
    'host_cache_callout.cc',
    'host_cache_impl.cc',
    'host_cache_log.cc',
    'host_cache_messages.cc',
    'host_cache_parsers.cc',
    'version.cc',
    dependencies: [CRYPTO_DEP],
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: HOOKS_PATH,
    install_rpath: INSTALL_RPATH,
    build_rpath: BUILD_RPATH,
    link_with: LIBS_BUILT_SO_FAR,
    name_suffix: 'so',
)
dhcp_host_cache_archive = static_library(
    'dhcp_host_cache',
    objects: dhcp_host_cache_lib.extract_all_objects(recursive: false),
)
subdir('libloadtests')
subdir('tests')

if KEA_MSG_COMPILER.found()
    target_gen_messages = run_target(
        'src-hooks-dhcp-host_cache-host_cache_messages',
        command: [
            CD_AND_RUN,
            TOP_SOURCE_DIR,
            KEA_MSG_COMPILER,
            'src/hooks/dhcp/host_cache/host_cache_messages.mes',
        ],
    )
    TARGETS_GEN_MESSAGES += [target_gen_messages]
endif
