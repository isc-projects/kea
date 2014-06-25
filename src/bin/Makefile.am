# The following build order must be maintained.
SUBDIRS = bind10 bindctl cfgmgr msgq cmdctl \
	usermgr stats tests  sockcreator dhcp4 dhcp6 \
	d2 sysinfo

if CONFIG_BACKEND_JSON
SUBDIRS += keactrl
endif

check-recursive: all-recursive
