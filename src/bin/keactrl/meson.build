keactrl_conf_data = configuration_data()
keactrl_conf_data.set('prefix', PREFIX)
sysconfdir = get_option('sysconfdir')
keactrl_conf_data.set('sysconfdir', '${prefix}/' + sysconfdir)
keactrl_conf_data.set('PACKAGE', 'kea')
keactrl_conf_data.set('exec_prefix', '${prefix}')
keactrl_conf_data.set('sbindir', '${prefix}/' + get_option('sbindir'))
if netconf_deps_found
    keactrl_conf_data.set('HAVE_NETCONF', 'yes')
else
    keactrl_conf_data.set('HAVE_NETCONF', 'no')
endif
keactrl_conf_data.set('EXTENDED_VERSION', project_version + ' (tarball)')
keactrl_conf_data.set('PACKAGE_VERSION', project_version)
keactrl_conf_data.set('runstatedir', '${prefix}/' + RUN_STATE_DIR + '/run')
keactrl_conf_data.set('localstatedir', '${prefix}/' + RUN_STATE_DIR)
kea_configfiles_destdir = f'@sysconfdir@/kea'
configure_file(
    input: 'keactrl.conf.in',
    output: 'keactrl.conf',
    configuration: keactrl_conf_data,
    install_dir: kea_configfiles_destdir,
)
configure_file(
    input: 'keactrl.in',
    output: 'keactrl',
    configuration: keactrl_conf_data,
    install_dir: get_option('sbindir'),
)
path_replacer = f'@TOP_BUILD_DIR@/tools/path_replacer.sh'
custom_target(
    input: 'kea-dhcp4.conf.pre',
    output: 'kea-dhcp4.conf',
    command: [path_replacer, '@INPUT@', '@OUTPUT@'],
    install: true,
    install_dir: kea_configfiles_destdir,
)
custom_target(
    input: 'kea-dhcp6.conf.pre',
    output: 'kea-dhcp6.conf',
    command: [path_replacer, '@INPUT@', '@OUTPUT@'],
    install: true,
    install_dir: kea_configfiles_destdir,
)
custom_target(
    input: 'kea-dhcp-ddns.conf.pre',
    output: 'kea-dhcp-ddns.conf',
    command: [path_replacer, '@INPUT@', '@OUTPUT@'],
    install: true,
    install_dir: kea_configfiles_destdir,
)
custom_target(
    input: 'kea-ctrl-agent.conf.pre',
    output: 'kea-ctrl-agent.conf',
    command: [path_replacer, '@INPUT@', '@OUTPUT@'],
    install: true,
    install_dir: kea_configfiles_destdir,
)
custom_target(
    input: 'kea-netconf.conf.pre',
    output: 'kea-netconf.conf',
    command: [path_replacer, '@INPUT@', '@OUTPUT@'],
    install: netconf_deps_found,
    install_dir: kea_configfiles_destdir,
)
