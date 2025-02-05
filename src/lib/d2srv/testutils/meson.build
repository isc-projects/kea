if not gtest.found()
    subdir_done()
endif

kea_d2srv_testutils_lib = static_library(
    'kea-d2srv-testutils',
    'nc_test_utils.cc',
    'stats_test_utils.cc',
    dependencies: [boost],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
)
