if not gtest.found()
    subdir_done()
endif

libs_testutils = [kea_d2srv_testutils_lib, kea_testutils_lib]
kea_d2srv_tests = executable(
    'kea-d2srv-tests',
    'run_unittests.cc',
    'd2_tsig_key_unittest.cc',
    'd2_update_message_unittests.cc',
    'd2_zone_unittests.cc',
    'dns_client_unittests.cc',
    'nc_trans_unittests.cc',
    dependencies: [boost, crypto, gtest],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: [kea_util_unittests_lib] + libs_testutils + LIBS_BUILT_SO_FAR,
)
test('kea_d2srv_tests', kea_d2srv_tests, protocol: 'gtest')
