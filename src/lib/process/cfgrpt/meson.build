mk_cfgrpt = f'@TOP_SOURCE_DIR@/tools/mk_cfgrpt.sh'
config_report_cc = custom_target(
    input: config_report,
    output: 'config_report.cc',
    command: [mk_cfgrpt, '@INPUT@', '@OUTPUT@'],
)
kea_cfgrpt_lib = library(
    'kea-cfgrpt',
    'cfgrpt.cc',
    config_report_cc,
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: 'lib',
    link_with: LIBS_BUILT_SO_FAR,
)
LIBS_BUILT_SO_FAR = [kea_cfgrpt_lib] + LIBS_BUILT_SO_FAR
subdir('tests')
kea_cfgrpt_headers = ['config_report.h']
install_headers(
    kea_cfgrpt_headers,
    preserve_path: true,
    subdir: 'kea/process/cfgrpt',
)
