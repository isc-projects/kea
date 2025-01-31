kea_asiolink_testutils_lib = static_library(
    'kea-asiolink-testutils',
    'test_tls.cc',
    'test_server_unix_socket.cc',
    'timed_signal.cc',
    cpp_args: [f'-DTEST_CA_DIR="@TEST_CA_DIR@"'],
    dependencies: [gtest, crypto],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR
)
