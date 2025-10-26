yangdir = DATADIR / 'kea/yang/modules/utils'
yang_utils_conf_data = configuration_data()
# Comment says sources (vs build)
yang_utils_conf_data.set('abs_top_srcdir', TOP_SOURCE_DIR)
yang_utils_conf_data.set('datarootdir', '${prefix}/' + DATADIR)
yang_utils_conf_data.set('prefix', PREFIX)
yang_utils_conf_data.set('LIBYANG_PREFIX', YANG_DEP.get_variable('prefix'))
yang_utils_conf_data.set('SYSREPO_PREFIX', SYSREPO_DEP.get_variable('prefix'))

check_hashes_sh = configure_file(
    input: 'check-hashes.sh.in',
    output: 'check-hashes.sh',
    configuration: yang_utils_conf_data,
)
check_revisions_sh = configure_file(
    input: 'check-revisions.sh.in',
    output: 'check-revisions.sh',
    configuration: yang_utils_conf_data,
)
configure_file(
    input: 'reinstall.sh.in',
    output: 'reinstall.sh',
    configuration: yang_utils_conf_data,
    install: true,
    install_dir: DATADIR / 'kea/yang/modules/utils',
)

test('check-hashes.sh', check_hashes_sh, suite: 'shell-tests')

test('check-revisions.sh', check_revisions_sh, suite: 'shell-tests')
