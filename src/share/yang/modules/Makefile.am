SUBDIRS = utils

yangmodulesdir = ${datarootdir}/${PACKAGE_NAME}/yang/modules

yangmodules_list  =
yangmodules_list += ietf-dhcpv6-client@2018-09-04.yang
yangmodules_list += ietf-interfaces@2018-02-20.yang
yangmodules_list += ietf-dhcpv6-options@2018-09-04.yang
yangmodules_list += ietf-dhcpv6-relay@2018-09-04.yang
yangmodules_list += ietf-dhcpv6-server@2018-09-04.yang
yangmodules_list += ietf-dhcpv6-types@2018-09-04.yang
yangmodules_list += ietf-inet-types@2013-07-15.yang
yangmodules_list += ietf-yang-types@2013-07-15.yang
yangmodules_list += kea-ctrl-agent@2019-08-12.yang
yangmodules_list += kea-dhcp-ddns@2022-07-27.yang
yangmodules_list += kea-dhcp-types@2022-12-27.yang
yangmodules_list += kea-dhcp4-server@2022-12-27.yang
yangmodules_list += kea-dhcp6-server@2022-12-27.yang
yangmodules_list += kea-types@2019-08-12.yang
yangmodules_list += keatest-module@2022-11-30.yang

EXTRA_DIST = hashes ${yangmodules_list}

if HAVE_NETCONF
yangmodules_DATA = ${yangmodules_list}
endif
