if not NETCONF_DEP.found()
    subdir_done()
endif

kea_yang_lib = shared_library(
    'kea-yang',
    'adaptor.cc',
    'adaptor_config.cc',
    'adaptor_host.cc',
    'adaptor_option.cc',
    'adaptor_pool.cc',
    'adaptor_subnet.cc',
    'translator.cc',
    'translator_class.cc',
    'translator_config.cc',
    'translator_control_socket.cc',
    'translator_database.cc',
    'translator_host.cc',
    'translator_logger.cc',
    'translator_option_data.cc',
    'translator_option_def.cc',
    'translator_pd_pool.cc',
    'translator_pool.cc',
    'translator_shared_network.cc',
    'translator_subnet.cc',
    dependencies: NETCONF_DEP,
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: LIBDIR,
    install_rpath: INSTALL_RPATH,
    build_rpath: BUILD_RPATH,
    link_with: LIBS_BUILT_SO_FAR,
    version: '86.0.0',
)
LIBS_BUILT_SO_FAR = [kea_yang_lib] + LIBS_BUILT_SO_FAR
kea_yang_headers = [
    'adaptor.h',
    'adaptor_config.h',
    'adaptor_host.h',
    'adaptor_option.h',
    'adaptor_pool.h',
    'adaptor_subnet.h',
    'netconf_error.h',
    'translator.h',
    'translator_class.h',
    'translator_config.h',
    'translator_control_socket.h',
    'translator_database.h',
    'translator_host.h',
    'translator_logger.h',
    'translator_option_data.h',
    'translator_option_def.h',
    'translator_pd_pool.h',
    'translator_pool.h',
    'translator_shared_network.h',
    'translator_subnet.h',
    'yang_models.h',
    'yang_revisions.h',
]
install_headers(kea_yang_headers, preserve_path: true, subdir: 'kea/yang')
subdir('testutils')
subdir('pretests')
subdir('tests')
