# The following build order must be maintained.
SUBDIRS = dhcp4 dhcp6 d2 agent lfc admin keactrl

if PERFDHCP
SUBDIRS += perfdhcp
endif

if KEA_SHELL
SUBDIRS += shell
endif

if HAVE_SYSREPO
SUBDIRS += netconf
endif

check-recursive: all-recursive
