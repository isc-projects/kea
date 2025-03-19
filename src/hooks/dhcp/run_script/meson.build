dhcp_run_script_lib = shared_library(
    'dhcp_run_script',
    'run_script.cc',
    'run_script_callouts.cc',
    'run_script_log.cc',
    'run_script_messages.cc',
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
dhcp_run_script_archive = static_library(
    'dhcp_run_script',
    objects: dhcp_run_script_lib.extract_all_objects(recursive: false),
)
# Do tests first
subdir('tests')
subdir('libloadtests')

if KEA_MSG_COMPILER.found()
    target_gen_messages = run_target(
        'src-hooks-dhcp-run_script-run_script_messages',
        command: [
            CD_AND_RUN,
            TOP_SOURCE_DIR,
            KEA_MSG_COMPILER,
            'src/hooks/dhcp/run_script/run_script_messages.mes',
        ],
    )
    TARGETS_GEN_MESSAGES += [target_gen_messages]
endif
