kea_config_backend_tests = executable(
    'kea-config_backend-tests',
    'config_backend_mgr_unittest.cc',
    'run_unittests.cc',
    dependencies: [gtest],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: [kea_testutils_lib, kea_util_unittests_lib] + LIBS_BUILT_SO_FAR,
)
test('kea_config_backend_tests', kea_config_backend_tests, protocol: 'gtest')
