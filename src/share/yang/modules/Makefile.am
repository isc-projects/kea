SUBDIRS = .

yangmodulesdir = ${datarootdir}/${PACKAGE_NAME}/yang/modules

yangmodules_list = ietf-dhcpv6-client@2018-09-04.yang
yangmodules_list += ietf-interfaces@2018-02-20.yang
yangmodules_list += ietf-dhcpv6-options@2018-09-04.yang
yangmodules_list += ietf-dhcpv6-relay@2018-09-04.yang
yangmodules_list += ietf-dhcpv6-server@2018-09-04.yang
yangmodules_list += ietf-dhcpv6-types@2018-09-04.yang
yangmodules_list += ietf-inet-types@2013-07-15.yang
yangmodules_list += ietf-yang-types@2013-07-15.yang
yangmodules_list += kea-ctrl-agent@2019-08-12.yang
yangmodules_list += kea-dhcp-ddns@2019-08-12.yang
yangmodules_list += kea-dhcp-types@2019-08-12.yang
yangmodules_list += kea-dhcp4-server@2019-08-12.yang
yangmodules_list += kea-dhcp6-server@2019-08-12.yang
yangmodules_list += kea-types@2019-08-12.yang
yangmodules_list += keatest-module@2018-11-20.yang

if HAVE_SYSREPO
yangmodules_DATA  = ${yangmodules_list}
endif

EXTRA_DIST = ${yangmodules_list}
