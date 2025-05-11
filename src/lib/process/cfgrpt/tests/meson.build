if not TESTS_OPT.enabled()
    subdir_done()
endif

kea_process_cfgrpt_tests = executable(
    'kea-process-cfgrpt-tests',
    'config_report_unittests.cc',
    'run_unittests.cc',
    dependencies: [GTEST_DEP],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: [kea_util_unittests_lib] + LIBS_BUILT_SO_FAR,
)
test('kea-process-cfgrpt-tests', kea_process_cfgrpt_tests, protocol: 'gtest')
