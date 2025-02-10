subdir('cfgrpt')
kea_process_lib = library(
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
    cpp_args: [f'-DDATA_DIR="@DHCP_DATA_DIR@"'],
    dependencies: [boost, gtest],
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: 'lib',
    link_with: LIBS_BUILT_SO_FAR,
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
