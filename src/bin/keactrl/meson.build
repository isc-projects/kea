keactrl_conf_data = configuration_data()
keactrl_conf_data.set('prefix', PREFIX)
keactrl_conf_data.set('sysconfdir', '${prefix}/' + SYSCONFDIR)
keactrl_conf_data.set('PACKAGE', 'kea')
keactrl_conf_data.set('exec_prefix', '${prefix}')
keactrl_conf_data.set('sbindir', '${prefix}/' + get_option('sbindir'))
if NETCONF_DEP.found()
    keactrl_conf_data.set('HAVE_NETCONF', 'yes')
else
    keactrl_conf_data.set('HAVE_NETCONF', 'no')
endif
keactrl_conf_data.set('EXTENDED_VERSION', PROJECT_VERSION + ' (tarball)')
keactrl_conf_data.set('PACKAGE_VERSION', PROJECT_VERSION)
keactrl_conf_data.set('runstatedir', '${prefix}/' + RUN_STATE_DIR + '/run')
keactrl_conf_data.set('localstatedir', '${prefix}/' + RUN_STATE_DIR)
kea_configfiles_destdir = f'@SYSCONFDIR@/kea'
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
configure_file(
    input: 'kea-dhcp4.conf.pre',
    output: 'kea-dhcp4.conf',
    command: [path_replacer, '@INPUT@', '@OUTPUT@'],
    install: true,
    install_dir: kea_configfiles_destdir,
)
configure_file(
    input: 'kea-dhcp6.conf.pre',
    output: 'kea-dhcp6.conf',
    command: [path_replacer, '@INPUT@', '@OUTPUT@'],
    install: true,
    install_dir: kea_configfiles_destdir,
)
configure_file(
    input: 'kea-dhcp-ddns.conf.pre',
    output: 'kea-dhcp-ddns.conf',
    command: [path_replacer, '@INPUT@', '@OUTPUT@'],
    install: true,
    install_dir: kea_configfiles_destdir,
)
configure_file(
    input: 'kea-ctrl-agent.conf.pre',
    output: 'kea-ctrl-agent.conf',
    command: [path_replacer, '@INPUT@', '@OUTPUT@'],
    install: true,
    install_dir: kea_configfiles_destdir,
)
configure_file(
    input: 'kea-netconf.conf.pre',
    output: 'kea-netconf.conf',
    command: [path_replacer, '@INPUT@', '@OUTPUT@'],
    install: NETCONF_DEP.found(),
    install_dir: kea_configfiles_destdir,
)
subdir('tests')
