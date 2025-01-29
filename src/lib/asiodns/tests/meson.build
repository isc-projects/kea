kea_asiodns_tests = executable(
    'kea-asiodns-tests',
    'io_fetch_unittest.cc',
    'run_unittests.cc',
    dependencies: [gtest],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR + [kea_testutils_lib, kea_util_unittests_lib],
)
test('kea_asiodns_tests', kea_asiodns_tests, protocol: 'gtest')
