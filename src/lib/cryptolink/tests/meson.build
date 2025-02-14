if not gtest.found()
    subdir_done()
endif

kea_cryptolink_tests = executable(
    'kea-cryptolink-tests',
    'crypto_unittests.cc',
    'hash_unittests.cc',
    'hmac_unittests.cc',
    'run_unittests.cc',
    dependencies: [gtest],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: [kea_util_unittests_lib] + LIBS_BUILT_SO_FAR,
)
test('kea-cryptolink-tests', kea_cryptolink_tests, protocol: 'gtest')
