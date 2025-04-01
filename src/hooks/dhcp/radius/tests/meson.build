if not TESTS_OPT.enabled()
    subdir_done()
endif

current_build_dir = meson.current_build_dir()
dhcp_radius_tests_libs = [
    dhcp_radius_archive,
    kea_dhcpsrv_testutils_lib,
    kea_dhcp_testutils_lib,
    kea_testutils_lib,
]
dhcp_radius_tests = executable(
    'dhcp-radius-tests',
    'access_unittests.cc',
    'accounting_unittests.cc',
    'async_request_unittests.cc',
    'attribute_test.cc',
    'attribute_unittests.cc',
    'backend_unittests.cc',
    'config_unittests.cc',
    'dictionary_unittests.cc',
    'exchange_unittests.cc',
    'message_unittests.cc',
    'run_unittests.cc',
    'server_unittests.cc',
    'sync_request_unittests.cc',
    'utils_unittests.cc',
    cpp_args: [
        f'-DTEST_DATA_BUILDDIR="@current_build_dir@"',
        f'-DDICTIONARY="@SYSCONFDIR_INSTALLED@/kea/radius/dictionary"',
        f'-DTEST_DICTIONARY="@TOP_SOURCE_DIR@/src/hooks/dhcp/radius/data/dictionary"',
    ],
    dependencies: [GTEST_DEP, CRYPTO_DEP],
    include_directories: [include_directories('.'), include_directories('..')] + INCLUDES,
    link_with: [dhcp_radius_tests_libs] + LIBS_BUILT_SO_FAR,
)
test('dhcp-radius-tests', dhcp_radius_tests, protocol: 'gtest')
