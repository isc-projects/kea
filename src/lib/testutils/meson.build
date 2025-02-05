if not gtest.found()
    subdir_done()
endif

kea_testutils_lib = static_library(
    'kea-testutils',
    'io_utils.cc',
    'log_utils.cc',
    'test_to_element.cc',
    'threaded_test.cc',
    'unix_control_client.cc',
    'user_context_utils.cc',
    dependencies: [gtest],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: [kea_util_unittests_lib] + LIBS_BUILT_SO_FAR,
)
