keactrl_conf_data = configuration_data()
keactrl_conf_data.set('PACKAGE', 'kea')
keactrl_conf_data.set('exec_prefix', '${prefix}')
keactrl_conf_data.set('prefix', PREFIX)
keactrl_conf_data.set('sbindir', '${prefix}/' + SBINDIR)
keactrl_conf_data.set('sysconfdir', '${prefix}/' + SYSCONFDIR)
if NETCONF_DEP.found()
    keactrl_conf_data.set('HAVE_NETCONF', 'yes')
else
    keactrl_conf_data.set('HAVE_NETCONF', 'no')
endif
keactrl_conf_data.set('EXTENDED_VERSION', SOURCE_OF_INSTALLATION)
keactrl_conf_data.set('PACKAGE_VERSION', PROJECT_VERSION)
keactrl_conf_data.set('runstatedir', '${prefix}/' + LOCALSTATEDIR + '/run')
keactrl_conf_data.set('localstatedir', '${prefix}/' + LOCALSTATEDIR)

kea_conf_data = configuration_data()
kea_conf_data.set('libdir', LIBDIR_INSTALLED)
kea_conf_data.set('localstatedir', LOCALSTATEDIR_INSTALLED)

kea_configfiles_destdir = SYSCONFDIR / 'kea'
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
    install_dir: SBINDIR,
)
configure_file(
    input: 'kea-dhcp4.conf.pre',
    output: 'kea-dhcp4.conf',
    configuration: kea_conf_data,
    install_dir: kea_configfiles_destdir,
)
configure_file(
    input: 'kea-dhcp6.conf.pre',
    output: 'kea-dhcp6.conf',
    configuration: kea_conf_data,
    install_dir: kea_configfiles_destdir,
)
configure_file(
    input: 'kea-dhcp-ddns.conf.pre',
    output: 'kea-dhcp-ddns.conf',
    configuration: kea_conf_data,
    install_dir: kea_configfiles_destdir,
)
configure_file(
    input: 'kea-ctrl-agent.conf.pre',
    output: 'kea-ctrl-agent.conf',
    configuration: kea_conf_data,
    install_dir: kea_configfiles_destdir,
)
configure_file(
    input: 'kea-netconf.conf.pre',
    output: 'kea-netconf.conf',
    configuration: kea_conf_data,
    install: NETCONF_DEP.found(),
    install_dir: kea_configfiles_destdir,
)
subdir('tests')
