if not TESTS_OPT.enabled()
    subdir_done()
endif

kea_asiodns_tests = executable(
    'kea-asiodns-tests',
    'io_fetch_unittest.cc',
    'run_unittests.cc',
    dependencies: [GTEST_DEP],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: [kea_testutils_lib, kea_util_unittests_lib] + LIBS_BUILT_SO_FAR,
)
test('kea-asiodns-tests', kea_asiodns_tests, protocol: 'gtest')
