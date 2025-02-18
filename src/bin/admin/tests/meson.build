if not gtest.found()
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
test('admin_tests.sh', admin_tests, is_parallel: false)
memfile_tests = configure_file(
    input: 'memfile_tests.sh.in',
    output: 'memfile_tests.sh',
    configuration: kea_admin_tests_conf_data,
)
test('memfile_tests.sh', memfile_tests, is_parallel: false)
mysql_tests = configure_file(
    input: 'mysql_tests.sh.in',
    output: 'mysql_tests.sh',
    configuration: kea_admin_tests_conf_data,
)
if mysql.found()
    test('kea_admin_mysql_tests.sh', mysql_tests, is_parallel: false)
endif
pgsql_tests = configure_file(
    input: 'pgsql_tests.sh.in',
    output: 'pgsql_tests.sh',
    configuration: kea_admin_tests_conf_data,
)
if postgresql.found()
    test('kea_admin_pgsql_tests.sh', pgsql_tests, is_parallel: false)
endif
# To create the output_dir
subdir('data')
