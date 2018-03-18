# The following build order must be maintained.
SUBDIRS = dhcp4 dhcp6 d2 agent perfdhcp admin lfc keactrl

if KEA_SHELL
SUBDIRS += shell
endif

if HAVE_SYSREPO
SUBDIRS += netconf
endif

check-recursive: all-recursive
