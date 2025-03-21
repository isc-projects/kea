mk_cfgrpt = TOP_SOURCE_DIR / 'tools/mk_cfgrpt.sh'
config_report_cc = configure_file(
    input: CONFIG_REPORT,
    output: 'config_report.cc',
    command: [mk_cfgrpt, '@INPUT@', '@OUTPUT@'],
)
kea_cfgrpt_lib = shared_library(
    'kea-cfgrpt',
    'cfgrpt.cc',
    config_report_cc,
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: LIBDIR,
    install_rpath: INSTALL_RPATH,
    build_rpath: BUILD_RPATH,
    link_with: LIBS_BUILT_SO_FAR,
    version: '2.0.0',
)
LIBS_BUILT_SO_FAR = [kea_cfgrpt_lib] + LIBS_BUILT_SO_FAR
subdir('tests')
kea_cfgrpt_headers = ['config_report.h']
install_headers(
    kea_cfgrpt_headers,
    preserve_path: true,
    subdir: 'kea/process/cfgrpt',
)
