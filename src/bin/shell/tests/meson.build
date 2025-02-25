if not gtest.found()
    subdir_done()
endif

shell_tests_conf_data = configuration_data()
shell_tests_conf_data.set('PYTHON', PYTHON.full_path())
shell_tests_conf_data.set('abs_top_builddir', TOP_BUILD_DIR)
shell_tests_conf_data.set('abs_top_srcdir', TOP_SOURCE_DIR)
shell_unittest = configure_file(
    input: 'shell_unittest.py.in',
    output: 'shell_unittest.py',
    configuration: shell_tests_conf_data,
)
test('shell_unittest.py', shell_unittest, is_parallel: false, priority: -1)
ca_basic_auth_tests = configure_file(
    input: 'ca_basic_auth_tests.sh.in',
    output: 'ca_basic_auth_tests.sh',
    configuration: shell_tests_conf_data,
)
test(
    'ca_basic_auth_tests.sh',
    ca_basic_auth_tests,
    is_parallel: false,
    priority: -1,
)
d2_basic_auth_tests = configure_file(
    input: 'd2_basic_auth_tests.sh.in',
    output: 'd2_basic_auth_tests.sh',
    configuration: shell_tests_conf_data,
)
test(
    'd2_basic_auth_tests.sh',
    d2_basic_auth_tests,
    is_parallel: false,
    priority: -1,
)
dhcp4_basic_auth_tests = configure_file(
    input: 'dhcp4_basic_auth_tests.sh.in',
    output: 'dhcp4_basic_auth_tests.sh',
    configuration: shell_tests_conf_data,
)
test(
    'dhcp4_basic_auth_tests.sh',
    dhcp4_basic_auth_tests,
    is_parallel: false,
    priority: -1,
)
dhcp6_basic_auth_tests = configure_file(
    input: 'dhcp6_basic_auth_tests.sh.in',
    output: 'dhcp6_basic_auth_tests.sh',
    configuration: shell_tests_conf_data,
)
test(
    'dhcp6_basic_auth_tests.sh',
    dhcp6_basic_auth_tests,
    is_parallel: false,
    priority: -1,
)
shell_d2_process_tests = configure_file(
    input: 'shell_d2_process_tests.sh.in',
    output: 'shell_d2_process_tests.sh',
    configuration: shell_tests_conf_data,
)
test(
    'shell_d2_process_tests.sh',
    shell_d2_process_tests,
    is_parallel: false,
    priority: -1,
)
shell_dhcp4_process_tests = configure_file(
    input: 'shell_dhcp4_process_tests.sh.in',
    output: 'shell_dhcp4_process_tests.sh',
    configuration: shell_tests_conf_data,
)
test(
    'shell_dhcp4_process_tests.sh',
    shell_dhcp4_process_tests,
    is_parallel: false,
    priority: -1,
)
shell_dhcp6_process_tests = configure_file(
    input: 'shell_dhcp6_process_tests.sh.in',
    output: 'shell_dhcp6_process_tests.sh',
    configuration: shell_tests_conf_data,
)
test(
    'shell_dhcp6_process_tests.sh',
    shell_dhcp6_process_tests,
    is_parallel: false,
    priority: -1,
)
tls_ca_process_tests = configure_file(
    input: 'tls_ca_process_tests.sh.in',
    output: 'tls_ca_process_tests.sh',
    configuration: shell_tests_conf_data,
)
test(
    'tls_ca_process_tests.sh',
    tls_ca_process_tests,
    is_parallel: false,
    priority: -1,
)
tls_d2_process_tests = configure_file(
    input: 'tls_d2_process_tests.sh.in',
    output: 'tls_d2_process_tests.sh',
    configuration: shell_tests_conf_data,
)
test(
    'tls_d2_process_tests.sh',
    tls_d2_process_tests,
    is_parallel: false,
    priority: -1,
)
tls_dhcp4_process_tests = configure_file(
    input: 'tls_dhcp4_process_tests.sh.in',
    output: 'tls_dhcp4_process_tests.sh',
    configuration: shell_tests_conf_data,
)
test(
    'tls_dhcp4_process_tests.sh',
    tls_dhcp4_process_tests,
    is_parallel: false,
    priority: -1,
)
tls_dhcp6_process_tests = configure_file(
    input: 'tls_dhcp6_process_tests.sh.in',
    output: 'tls_dhcp6_process_tests.sh',
    configuration: shell_tests_conf_data,
)
test(
    'tls_dhcp6_process_tests.sh',
    tls_dhcp6_process_tests,
    is_parallel: false,
    priority: -1,
)
