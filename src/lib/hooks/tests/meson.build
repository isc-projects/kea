if not gtest.found()
    subdir_done()
endif

# Generate marker_file.h test_libraries.h
kea_hooks_tests = executable(
    'kea-hooks-tests',
    'callout_handle_associate_unittest.cc',
    'callout_handle_unittest.cc',
    'callout_manager_unittest.cc',
    'handles_unittest.cc',
    # 'hooks_manager_unittest.cc',
    # 'library_manager_collection_unittest.cc',
    # 'library_manager_unittest.cc',
    'parking_lots_unittest.cc',
    'run_unittests.cc',
    'server_hooks_unittest.cc',
    dependencies: [gtest],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: [kea_util_unittests_lib] + LIBS_BUILT_SO_FAR,
)
test('kea_hooks_tests', kea_hooks_tests, protocol: 'gtest')
