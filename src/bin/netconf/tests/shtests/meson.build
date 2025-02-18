if not gtest.found()
    subdir_done()
endif

netconf_shtests_conf_data = configuration_data()
netconf_shtests_conf_data.set('abs_top_builddir', TOP_BUILD_DIR)
netconf_shtests = configure_file(
    input: 'netconf_tests.sh.in',
    output: 'netconf_tests.sh',
    configuration: netconf_shtests_conf_data,
)
test('netconf_tests.sh', netconf_shtests, is_parallel: false)
