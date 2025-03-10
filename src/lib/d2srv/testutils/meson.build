if not TESTS_OPT.enabled()
    subdir_done()
endif

kea_d2srv_testutils_lib = static_library(
    'kea-d2srv-testutils',
    'nc_test_utils.cc',
    'stats_test_utils.cc',
    dependencies: [CRYPTO_DEP, GTEST_DEP],
    include_directories: [include_directories('.')] + INCLUDES,
)
