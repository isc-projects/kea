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
test('kea-log-tests', kea_log_tests, protocol: 'gtest')

kea_log_init_tests = executable(
    'kea-log-init-tests',
    'run_initializer_unittests.cc',
    'message_initializer_1_unittest.cc',
    'message_initializer_1a_unittest.cc',
    dependencies: [gtest, log4cplus],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: [kea_util_unittests_lib] + LIBS_BUILT_SO_FAR,
)
test('kea-log-init-tests', kea_log_init_tests, protocol: 'gtest')

executable(
    'logger_example',
    'logger_example.cc',
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: [kea_util_unittests_lib] + LIBS_BUILT_SO_FAR,
)
executable(
    'init_logger_test',
    'init_logger_test.cc',
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: [kea_util_unittests_lib] + LIBS_BUILT_SO_FAR,
)
executable(
    'buffer_logger_test',
    'buffer_logger_test.cc',
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: [kea_util_unittests_lib] + LIBS_BUILT_SO_FAR,
)
executable(
    'logger_lock_test',
    'logger_lock_test.cc',
    'log_test_messages.cc',
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
current_build_dir = meson.current_build_dir()
shtests_conf_data.set('abs_builddir', current_build_dir)
foreach shtest : shtests
    shfile = configure_file(
        input: shtest + '.in',
        output: shtest,
        configuration: shtests_conf_data,
    )
    name = 'kea-log-' + shtest
    test(
        name,
        shfile,
        workdir: current_build_dir,
        is_parallel: false,
        priority: -1,
    )
endforeach

if KEA_MSG_COMPILER.found()
    current_source_dir = meson.current_source_dir()
    target_gen_messages = run_target(
        'src-lib-log-tests-log_test_messages',
        command: [
            CD_AND_RUN,
            TOP_SOURCE_DIR,
            KEA_MSG_COMPILER,
            'src/lib/log/tests/log_test_messages.mes',
        ],
    )
    TARGETS_GEN_MESSAGES += [target_gen_messages]
endif
