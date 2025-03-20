if not TESTS_OPT.enabled()
    subdir_done()
endif

kea_admin_tests_conf_data = configuration_data()
kea_admin_tests_conf_data.set('abs_top_builddir', TOP_BUILD_DIR)
kea_admin_tests_conf_data.set('abs_top_srcdir', TOP_SOURCE_DIR)
admin_tests = configure_file(
    input: 'admin_tests.sh.in',
    output: 'admin_tests.sh',
    configuration: kea_admin_tests_conf_data,
)
test(
    'admin_tests.sh',
    admin_tests,
    is_parallel: false,
    priority: -1,
    suite: 'shell-tests',
)
memfile_tests = configure_file(
    input: 'memfile_tests.sh.in',
    output: 'memfile_tests.sh',
    configuration: kea_admin_tests_conf_data,
)
test(
    'memfile_tests.sh',
    memfile_tests,
    # depends: [kea_admin, kea_dhcp4, kea_dhcp6, kea_lfc],
    is_parallel: false,
    priority: -1,
    suite: 'shell-tests',
)
mysql_tests = configure_file(
    input: 'mysql_tests.sh.in',
    output: 'mysql_tests.sh',
    configuration: kea_admin_tests_conf_data,
)
if MYSQL_DEP.found()
    test(
        'kea_admin_mysql_tests.sh',
        mysql_tests,
        is_parallel: false,
        priority: -1,
        suite: 'shell-tests',
        timeout: 240,
    )
endif
pgsql_tests = configure_file(
    input: 'pgsql_tests.sh.in',
    output: 'pgsql_tests.sh',
    configuration: kea_admin_tests_conf_data,
)
if POSTGRESQL_DEP.found()
    test(
        'kea_admin_pgsql_tests.sh',
        pgsql_tests,
        is_parallel: false,
        priority: -1,
        suite: 'shell-tests',
        timeout: 240,
    )
endif
# To create the output_dir
subdir('data')
