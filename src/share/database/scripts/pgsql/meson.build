postgresql_script_conf_data = configuration_data()
postgresql_script_conf_data.set('prefix', get_option('prefix'))
postgresql_script_conf_data.set('abs_top_builddir', TOP_BUILD_DIR)
postgresql_script_conf_data.set(
    'datarootdir',
    '${prefix}/' + get_option('datadir'),
)
postgresql_script_conf_data.set('PACKAGE_NAME', 'kea')
configure_file(
    input: 'wipe_data.sh.in',
    output: 'wipe_data.sh',
    configuration: postgresql_script_conf_data,
)
configure_file(
    input: 'dhcpdb_create.pgsql',
    output: 'dhcpdb_create.pgsql',
    copy: true,
)
configure_file(
    input: 'dhcpdb_drop.pgsql',
    output: 'dhcpdb_drop.pgsql',
    copy: true,
)
# configure upgrade scripts
# install
