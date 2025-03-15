kea_admin_conf_data = configuration_data()
kea_admin_conf_data.set('prefix', PREFIX)
kea_admin_conf_data.set('exec_prefix', '${prefix}')
kea_admin_conf_data.set('datarootdir', '${prefix}/' + DATADIR)
kea_admin_conf_data.set('PACKAGE', 'kea')
kea_admin_conf_data.set('PACKAGE_NAME', 'kea')
kea_admin_conf_data.set('PACKAGE_VERSION', PROJECT_VERSION)
kea_admin_conf_data.set('EXTENDED_VERSION', PROJECT_VERSION + ' (tarball)')
kea_admin_conf_data.set('abs_top_builddir', TOP_BUILD_DIR)
kea_admin_conf_data.set('abs_top_srcdir', TOP_SOURCE_DIR)
kea_admin_conf_data.set('sbindir', '${prefix}/' + SBINDIR)
kea_admin_conf_data.set('variables', 'variables')
configure_file(
    input: 'kea-admin.in',
    output: 'kea-admin',
    configuration: kea_admin_conf_data,
    install: true,
    install_dir: SBINDIR,
)
adminscriptsdir = f'@DATADIR@/kea/scripts'
configure_file(
    input: 'admin-utils.sh.in',
    output: 'admin-utils.sh',
    copy: true,
    install: true,
    install_dir: adminscriptsdir,
)
subdir('tests')
