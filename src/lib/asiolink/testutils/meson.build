if not gtest.found()
    subdir_done()
endif

kea_asiolink_testutils_lib = static_library(
    'kea-asiolink-testutils',
    'test_tls.cc',
    'test_server_unix_socket.cc',
    'timed_signal.cc',
    cpp_args: [f'-DTEST_CA_DIR="@TEST_CA_DIR@"'],
    dependencies: [crypto, gtest],
    include_directories: [include_directories('.')] + INCLUDES,
)

if crypto.name() == openssl.name()
    executable(
        'openssl_sample_client',
        'openssl_sample_client.cc',
        cpp_args: [f'-DTEST_CA_DIR="@TEST_CA_DIR@"'],
        dependencies: [gtest, openssl],
        include_directories: [include_directories('.')] + INCLUDES,
        link_with: LIBS_BUILT_SO_FAR,
    )
    executable(
        'openssl_sample_server',
        'openssl_sample_server.cc',
        cpp_args: [f'-DTEST_CA_DIR="@TEST_CA_DIR@"'],
        dependencies: [gtest, openssl],
        include_directories: [include_directories('.')] + INCLUDES,
        link_with: LIBS_BUILT_SO_FAR,
    )
elif crypto.name() == botan.name()
    executable(
        'botan_sample_client',
        'botan_sample_client.cc',
        cpp_args: [f'-DTEST_CA_DIR="@TEST_CA_DIR@"'],
        dependencies: [gtest, botan],
        include_directories: [include_directories('.')] + INCLUDES,
        link_with: LIBS_BUILT_SO_FAR,
    )
    executable(
        'botan_sample_server',
        'botan_sample_server.cc',
        cpp_args: [f'-DTEST_CA_DIR="@TEST_CA_DIR@"'],
        dependencies: [gtest, botan],
        include_directories: [include_directories('.')] + INCLUDES,
        link_with: LIBS_BUILT_SO_FAR,
    )
endif
