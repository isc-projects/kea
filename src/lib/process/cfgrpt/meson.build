config_report_cc = configure_file(
    input: 'config_report.cc.in',
    output: 'config_report.cc',
    configuration: conf_data,
)

kea_cfgrpt_lib = library(
    'kea-cfgrpt',
    'cfgrpt.cc',
    config_report_cc,
    'config_report.h',
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: 'lib',
    link_with: LIBS_BUILT_SO_FAR,
)
LIBS_BUILT_SO_FAR = [kea_cfgrpt_lib] + LIBS_BUILT_SO_FAR
