if not gtest.found()
    subdir_done()
endif

keactrl_tests_conf_data = configuration_data()
keactrl_tests_conf_data.set('abs_top_builddir', TOP_BUILD_DIR)
if NETCONF_DEPS_FOUND
    keactrl_tests_conf_data.set('HAVE_NETCONF', 'yes')
else
    keactrl_tests_conf_data.set('HAVE_NETCONF', 'no')
endif
keactrl_tests_conf_data.set('PACKAGE_VERSION', PROJECT_VERSION)
configure_file(
    input: 'keactrl_tests.sh.in',
    output: 'keactrl_tests.sh',
    configuration: keactrl_tests_conf_data,
)
