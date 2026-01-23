subdir('cfgrpt')
kea_process_lib = shared_library(
    'kea-process',
    'config_base.cc',
    'config_ctl_info.cc',
    'config_ctl_parser.cc',
    'daemon.cc',
    'd_cfg_mgr.cc',
    'd_controller.cc',
    'd_log.cc',
    'logging_info.cc',
    'log_parser.cc',
    'process_messages.cc',
    'redact_config.cc',
    cpp_args: [
        f'-DPIDFILE_DIR="@RUNSTATEDIR_INSTALLED@"',
        f'-DLOGFILE_DIR="@LOGDIR_INSTALLED@"',
    ],
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: LIBDIR,
    install_rpath: INSTALL_RPATH,
    build_rpath: BUILD_RPATH,
    link_with: LIBS_BUILT_SO_FAR,
    version: '104.0.0',
)
LIBS_BUILT_SO_FAR = [kea_process_lib] + LIBS_BUILT_SO_FAR
subdir('testutils')
subdir('tests')
kea_process_headers = [
    'cb_ctl_base.h',
    'config_base.h',
    'config_ctl_info.h',
    'config_ctl_parser.h',
    'daemon.h',
    'd_cfg_mgr.h',
    'd_controller.h',
    'd_log.h',
    'd_process.h',
    'logging_info.h',
    'log_parser.h',
    'process_messages.h',
    'redact_config.h',
]
install_headers(kea_process_headers, preserve_path: true, subdir: 'kea/process')

if KEA_MSG_COMPILER.found()
    current_source_dir = meson.current_source_dir()
    target_gen_messages = run_target(
        'src-lib-process-process_messages',
        command: [
            CD_AND_RUN,
            TOP_SOURCE_DIR,
            KEA_MSG_COMPILER,
            'src/lib/process/process_messages.mes',
        ],
    )
    TARGETS_GEN_MESSAGES += [target_gen_messages]
endif
