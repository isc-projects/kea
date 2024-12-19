kea_cryptolink_tests_exe = executable('kea-cryptolink-tests',
  'crypto_unittests.cc',
  'hash_unittests.cc',
  'hmac_unittests.cc',
  'run_unittests.cc',
  dependencies: [gtest],
  include_directories: [include_directories('.')] + includes,
  link_with: libs_built_so_far + [kea_util_unittests_lib],
)
test('kea_cryptolink_tests_exe', kea_cryptolink_tests_exe)
