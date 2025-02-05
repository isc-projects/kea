if not gtest.found()
    subdir_done()
endif

kea_cc_tests = executable(
    'kea-cc-tests',
    'command_interpreter_unittests.cc',
    'data_file_unittests.cc',
    'data_unittests.cc',
    'element_value_unittests.cc',
    'json_feed_unittests.cc',
    'run_unittests.cc',
    'server_tag_unittest.cc',
    'simple_parser_unittest.cc',
    'stamped_element_unittest.cc',
    'stamped_value_unittest.cc',
    'user_context_unittests.cc',
    dependencies: [gtest],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: [kea_util_unittests_lib] + LIBS_BUILT_SO_FAR,
)
test('kea_cc_tests', kea_cc_tests, protocol: 'gtest')
