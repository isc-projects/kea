# The following build order must be maintained.
SUBDIRS = dhcp4 dhcp6 netconf d2 agent perfdhcp admin lfc keactrl

if KEA_SHELL
SUBDIRS += shell
endif

check-recursive: all-recursive
