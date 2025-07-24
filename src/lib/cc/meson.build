kea_cc_lib_cpp_args = []
if TESTS_OPT.enabled()
    kea_cc_lib_cpp_args = ['-DALLOW_KEATEST']
endif
kea_cc_lib = shared_library(
    'kea-cc',
    'base_stamped_element.cc',
    'command_interpreter.cc',
    'data.cc',
    'default_credentials.cc',
    'json_feed.cc',
    'server_tag.cc',
    'simple_parser.cc',
    'stamped_element.cc',
    'stamped_value.cc',
    'user_context.cc',
    cpp_args: kea_cc_lib_cpp_args,
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: LIBDIR,
    install_rpath: INSTALL_RPATH,
    build_rpath: BUILD_RPATH,
    link_with: LIBS_BUILT_SO_FAR,
    version: '93.0.0',
)
LIBS_BUILT_SO_FAR = [kea_cc_lib] + LIBS_BUILT_SO_FAR
subdir('tests')
kea_cc_headers = [
    'base_stamped_element.h',
    'cfg_to_element.h',
    'command_interpreter.h',
    'data.h',
    'default_credentials.h',
    'dhcp_config_error.h',
    'element_value.h',
    'json_feed.h',
    'server_tag.h',
    'simple_parser.h',
    'stamped_element.h',
    'stamped_value.h',
    'user_context.h',
]
install_headers(kea_cc_headers, preserve_path: true, subdir: 'kea/cc')
