kea_hooks_lib = shared_library(
    'kea-hooks',
    'callout_handle.cc',
    'callout_handle_associate.cc',
    'callout_manager.cc',
    'hooks_config.cc',
    'hooks_log.cc',
    'hooks_manager.cc',
    'hooks_messages.cc',
    'hooks_parser.cc',
    'libinfo.cc',
    'library_handle.cc',
    'library_manager.cc',
    'library_manager_collection.cc',
    'server_hooks.cc',
    cpp_args: [
        f'-DDEFAULT_HOOK_SCRIPTS_PATH="@PREFIX@/@DATADIR@/kea/scripts"',
        f'-DDEFAULT_HOOKS_PATH="@DEFAULT_HOOKS_PATH@"'
    ],
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: LIBDIR,
    install_rpath: INSTALL_RPATH,
    build_rpath: BUILD_RPATH,
    link_with: LIBS_BUILT_SO_FAR,
    version: '134.0.0',
)
LIBS_BUILT_SO_FAR = [kea_hooks_lib] + LIBS_BUILT_SO_FAR
subdir('tests')
kea_hooks_headers = [
    'callout_handle.h',
    'callout_handle_associate.h',
    'callout_manager.h',
    'hooks.h',
    'hooks_config.h',
    'hooks_log.h',
    'hooks_manager.h',
    'hooks_messages.h',
    'hooks_parser.h',
    'libinfo.h',
    'library_handle.h',
    'library_manager.h',
    'library_manager_collection.h',
    'parking_lots.h',
    'pointer_converter.h',
    'server_hooks.h',
]
install_headers(kea_hooks_headers, preserve_path: true, subdir: 'kea/hooks')

if KEA_MSG_COMPILER.found()
    current_source_dir = meson.current_source_dir()
    target_gen_messages = run_target(
        'src-lib-hooks-hooks_messages',
        command: [
            CD_AND_RUN,
            TOP_SOURCE_DIR,
            KEA_MSG_COMPILER,
            'src/lib/hooks/hooks_messages.mes',
        ],
    )
    TARGETS_GEN_MESSAGES += [target_gen_messages]
endif
