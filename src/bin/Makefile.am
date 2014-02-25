if WANT_EXPERIMENTAL_RESOLVER
# Build resolver only with --enable-experimental-resolver
experimental_resolver = resolver
endif

SUBDIRS = bind10 bindctl cfgmgr ddns loadzone msgq cmdctl auth xfrin \
	xfrout usermgr zonemgr stats tests $(experimental_resolver) \
	sockcreator dhcp4 dhcp6 d2 dbutil sysinfo

if USE_SHARED_MEMORY
# Build the memory manager only if we have shared memory.
# It is useless without it.
SUBDIRS += memmgr
endif

check-recursive: all-recursive
