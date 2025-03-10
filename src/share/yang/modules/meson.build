if not NETCONF_DEP.found()
    subdir_done()
endif

subdir('utils')

yangmodulesdir = f'@DATADIR@/kea/yang/modules'
yangmodules_list = [
    'ietf-dhcpv6-client@2018-09-04.yang',
    'ietf-dhcpv6-options@2018-09-04.yang',
    'ietf-dhcpv6-relay@2018-09-04.yang',
    'ietf-dhcpv6-server@2018-09-04.yang',
    'ietf-dhcpv6-types@2018-09-04.yang',
    'ietf-inet-types@2013-07-15.yang',
    'ietf-interfaces@2018-02-20.yang',
    'ietf-yang-types@2013-07-15.yang',
    'kea-ctrl-agent@2019-08-12.yang',
    'kea-dhcp-ddns@2022-07-27.yang',
    'kea-dhcp-types@2024-05-29.yang',
    'kea-dhcp4-server@2024-05-29.yang',
    'kea-dhcp6-server@2024-05-29.yang',
    'kea-types@2019-08-12.yang',
    'keatest-module@2022-11-30.yang',
]
list = run_command('utils/grabber.sh', check: true)
grabbed_modules = list.stdout().strip().split('\n')
foreach file : grabbed_modules
    assert(
        yangmodules_list.contains(file),
        'module file list mismatch: no ' + file,
    )
endforeach
install_data(yangmodules_list, install_dir: yangmodulesdir)
