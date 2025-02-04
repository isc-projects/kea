mysql_script_conf_data = configuration_data()
mysql_script_conf_data.set('prefix', get_option('prefix'))
mysql_script_conf_data.set('abs_top_builddir', TOP_BUILD_DIR)
mysql_script_conf_data.set('datarootdir', '${prefix}/' + get_option('datadir'))
mysql_script_conf_data.set('PACKAGE_NAME', 'kea')
configure_file(
    input: 'wipe_data.sh.in',
    output: 'wipe_data.sh',
    configuration: mysql_script_conf_data,
)
configure_file(
    input: 'dhcpdb_create.mysql',
    output: 'dhcpdb_create.mysql',
    copy: true,
)
configure_file(
    input: 'dhcpdb_drop.mysql',
    output: 'dhcpdb_drop.mysql',
    copy: true,
)
# configure upgrade scripts
# install
