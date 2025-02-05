if not gtest.found()
    subdir_done()
endif

kea_log_tests = executable(
    'kea-log-tests',
    'buffer_appender_unittest.cc',
    'logger_level_impl_unittest.cc',
    'logger_level_unittest.cc',
    'logger_manager_unittest.cc',
    'logger_name_unittest.cc',
    'logger_specification_unittest.cc',
    'logger_support_unittest.cc',
    'logger_unittest.cc',
    'log_formatter_unittest.cc',
    'log_test_messages.cc',
    'message_dictionary_unittest.cc',
    'message_reader_unittest.cc',
    'output_option_unittest.cc',
    'run_unittests.cc',
    cpp_args: [f'-DTEMP_DIR="@TOP_BUILD_DIR@"'],
    dependencies: [gtest, log4cplus],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: [kea_util_unittests_lib] + LIBS_BUILT_SO_FAR,
)
test('kea_log_tests', kea_log_tests, protocol: 'gtest')

kea_log_init_tests = executable(
    'kea-log-init-tests',
    'run_initializer_unittests.cc',
    'message_initializer_1_unittest.cc',
    'message_initializer_1a_unittest.cc',
    dependencies: [boost, gtest, log4cplus],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: [kea_util_unittests_lib] + LIBS_BUILT_SO_FAR,
)
test('kea_log_init_tests', kea_log_init_tests, protocol: 'gtest')

logger_example = executable(
    'logger_example',
    'logger_example.cc',
    dependencies: [boost],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: [kea_util_unittests_lib] + LIBS_BUILT_SO_FAR,
)
init_logger_test = executable(
    'init_logger_test',
    'init_logger_test.cc',
    dependencies: [boost],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: [kea_util_unittests_lib] + LIBS_BUILT_SO_FAR,
)
buffer_logger_test = executable(
    'buffer_logger_test',
    'buffer_logger_test.cc',
    dependencies: [boost],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: [kea_util_unittests_lib] + LIBS_BUILT_SO_FAR,
)
logger_lock_test = executable(
    'logger_lock_test',
    'logger_lock_test.cc',
    'log_test_messages.cc',
    dependencies: [boost],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: [kea_util_unittests_lib] + LIBS_BUILT_SO_FAR,
)
shtests = [
    'buffer_logger_test.sh',
    'console_test.sh',
    'destination_test.sh',
    'init_logger_test.sh',
    'local_file_test.sh',
    'logger_lock_test.sh',
    'severity_test.sh',
]
shtests_conf_data = configuration_data()
shtests_conf_data.set('abs_top_builddir', TOP_BUILD_DIR)
CURRENT_BUILD_DIR = meson.current_build_dir()
shtests_conf_data.set('abs_builddir', CURRENT_BUILD_DIR)
foreach shtest : shtests
    shfile = configure_file(
        input: shtest + '.in',
        output: shtest,
        configuration: shtests_conf_data,
    )
    name = 'kea_log_' + shtest
    test(name, shfile, workdir: CURRENT_BUILD_DIR, is_parallel: false)
endforeach
