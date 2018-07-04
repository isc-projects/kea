# The following build order must be maintained.
SUBDIRS = dhcp4 dhcp6 d2 agent perfdhcp admin lfc keactrl kea_config_tool

if KEA_SHELL
SUBDIRS += shell
endif

check-recursive: all-recursive
