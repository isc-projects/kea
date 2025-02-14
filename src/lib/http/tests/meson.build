if not gtest.found()
    subdir_done()
endif

current_source_dir = meson.current_source_dir()
libs_testutils = [kea_testutils_lib, kea_asiolink_testutils_lib]
kea_http_tests = executable(
    'kea-http-tests',
    'basic_auth_config_unittests.cc',
    'basic_auth_unittests.cc',
    'cfg_http_header_unittests.cc',
    'client_mt_unittests.cc',
    'connection_pool_unittests.cc',
    'date_time_unittests.cc',
    'http_client_unittests.cc',
    'http_header_unittests.cc',
    'http_server_unittests.cc',
    'post_request_json_unittests.cc',
    'request_parser_unittests.cc',
    'request_unittests.cc',
    'response_creator_unittests.cc',
    'response_json_unittests.cc',
    'response_parser_unittests.cc',
    'response_unittests.cc',
    'run_unittests.cc',
    'tls_client_unittests.cc',
    'tls_server_unittests.cc',
    'url_unittests.cc',
    cpp_args: [
        f'-DTEST_CA_DIR="@TEST_CA_DIR@"',
        f'-DDATA_DIR="@current_source_dir@/testdata"',
    ],
    dependencies: [gtest, crypto],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: [kea_util_unittests_lib, libs_testutils] + LIBS_BUILT_SO_FAR,
)
test(
    'kea-http-tests',
    kea_http_tests,
    protocol: 'gtest',
    is_parallel: false,
    priority: -1,
)
