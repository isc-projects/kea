subdir('interprocess')
kea_log_lib = shared_library(
    'kea-log',
    'buffer_appender_impl.cc',
    'logger.cc',
    'logger_impl.cc',
    'logger_level.cc',
    'logger_level_impl.cc',
    'logger_manager.cc',
    'logger_manager_impl.cc',
    'logger_name.cc',
    'logger_support.cc',
    'logger_unittest_support.cc',
    'logimpl_messages.cc',
    'log_dbglevels.cc',
    'log_formatter.cc',
    'log_messages.cc',
    'message_dictionary.cc',
    'message_initializer.cc',
    'message_reader.cc',
    'output_option.cc',
    cpp_args: [f'-DTOP_BUILDDIR="@TOP_BUILD_DIR@"'],
    dependencies: [LOG4CPLUS_DEP],
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: LIBDIR,
    install_rpath: INSTALL_RPATH,
    build_rpath: BUILD_RPATH,
    link_with: LIBS_BUILT_SO_FAR,
    version: '72.0.0',
)
LIBS_BUILT_SO_FAR = [kea_log_lib] + LIBS_BUILT_SO_FAR
subdir('compiler')
subdir('tests')
kea_log_headers = [
    'buffer_appender_impl.h',
    'log_dbglevels.h',
    'log_formatter.h',
    'logger.h',
    'logger_impl.h',
    'logger_level.h',
    'logger_level_impl.h',
    'logger_manager.h',
    'logger_manager_impl.h',
    'logger_name.h',
    'logger_specification.h',
    'logger_support.h',
    'logger_unittest_support.h',
    'logimpl_messages.h',
    'log_messages.h',
    'macros.h',
    'message_dictionary.h',
    'message_exception.h',
    'message_initializer.h',
    'message_reader.h',
    'message_types.h',
    'output_option.h',
]
install_headers(kea_log_headers, preserve_path: true, subdir: 'kea/log')

if KEA_MSG_COMPILER.found()
    current_source_dir = meson.current_source_dir()
    target_gen_messages = run_target(
        'src-lib-log-log_messages',
        command: [
            CD_AND_RUN,
            TOP_SOURCE_DIR,
            KEA_MSG_COMPILER,
            'src/lib/log/log_messages.mes',
        ],
    )
    TARGETS_GEN_MESSAGES += [target_gen_messages]
    target_gen_messages = run_target(
        'src-lib-log-logimpl_messages',
        command: [
            CD_AND_RUN,
            TOP_SOURCE_DIR,
            KEA_MSG_COMPILER,
            'src/lib/log/logimpl_messages.mes',
        ],
    )
    TARGETS_GEN_MESSAGES += [target_gen_messages]
endif
