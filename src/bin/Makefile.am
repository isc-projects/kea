# The following build order must be maintained.
SUBDIRS = dhcp4 dhcp6 d2

if CONFIG_BACKEND_JSON
SUBDIRS += keactrl
endif

check-recursive: all-recursive
