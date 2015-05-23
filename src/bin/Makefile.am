# The following build order must be maintained.
SUBDIRS = cfgrpt dhcp4 dhcp6 d2 perfdhcp admin lfc

if CONFIG_BACKEND_JSON
SUBDIRS += keactrl
endif

check-recursive: all-recursive
