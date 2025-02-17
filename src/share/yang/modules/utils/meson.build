yangdir = f'@DATADIR@/kea/yang/modules/utils'
yang_utils_conf_data = configuration_data()
# Comment says sources (vs build)
yang_utils_conf_data.set('abs_top_builddir', TOP_BUILD_DIR)
# Beware that top_srcdir here must be a relative path.
yang_utils_conf_data.set('top_srcdir', '../../../../..')
yang_utils_conf_data.set('datarootdir', f'@PREFIX@/@DATADIR@')
yang_utils_conf_data.set('prefix', PREFIX)
yang_utils_conf_data.set(
    'LIBYANG_PREFIX',
    netconf_deps['yang'].get_variable('prefix'),
)
yang_utils_conf_data.set(
    'SYSREPO_PREFIX',
    netconf_deps['sysrepo'].get_variable('prefix'),
)

configure_file(
    input: 'check-hashes.sh.in',
    output: 'check-hashes.sh',
    configuration: yang_utils_conf_data,
)
configure_file(
    input: 'check-revisions.sh.in',
    output: 'check-revisions.sh',
    configuration: yang_utils_conf_data,
)
configure_file(
    input: 'reinstall.sh.in',
    output: 'reinstall.sh',
    configuration: yang_utils_conf_data,
    install: true,
    install_dir: 'share/kea/yang/modules/utils',
)
