# The following build order must be maintained.
SUBDIRS = lfc dhcp4 dhcp6 d2 agent admin keactrl

if PERFDHCP
SUBDIRS += perfdhcp
endif

if KEA_SHELL
SUBDIRS += shell
endif

if HAVE_NETCONF
SUBDIRS += netconf
endif

check-recursive: all-recursive
