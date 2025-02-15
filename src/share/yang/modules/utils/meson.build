yangdir = f'@DATADIR@/kea/yang/modules/utils'
yang_utils_conf_data = configuration_data()
# Comment says sources (vs build)
yang_utils_conf_data.set('abs_top_builddir', TOP_SOURCE_DIR)
# Beware that top_srcdir here must be a relative path.
yang_utils_conf_data.set('top_srcdir', '../../../../..')
yang_utils_conf_data.set('datarootdir', f'@PREFIX@/@DATADIR@')
yang_lint = find_program('/opt/bin/yanglint', required: false)
if yang_lint.found()
    yang_utils_conf_data.set('LIBYANG_PREFIX', '/opt')
    yang_utils_conf_data.set('SYSREPO_PREFIX', '/opt')
else
    yang_utils_conf_data.set('SYSREPO_PREFIX', '/usr/local')
    yang_lint = find_program('/usr/local/bin/yanglint', required: false)
    if yang_lint.found()
        yang_utils_conf_data.set('LIBYANG_PREFIX', '/usr/local')
    else
        yang_lint = find_program('yanglint', required: true)
        yang_utils_conf_data.set('LIBYANG_PREFIX', '')
    endif
endif

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
)
