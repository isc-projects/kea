if not gtest.found()
    subdir_done()
endif

kea_exceptions_tests = executable(
    'kea-exceptions-tests',
    'exceptions_unittest.cc',
    'run_unittests.cc',
    dependencies: [gtest],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
)
test('kea-exceptions-tests', kea_exceptions_tests, protocol: 'gtest')
