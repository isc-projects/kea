kea_cryptolink_tests = executable(
    'kea-cryptolink-tests',
    'crypto_unittests.cc',
    'hash_unittests.cc',
    'hmac_unittests.cc',
    'run_unittests.cc',
    dependencies: [gtest],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR + [kea_util_unittests_lib],
)
test('kea_cryptolink_tests', kea_cryptolink_tests, protocol: 'gtest')
