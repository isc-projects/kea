if WANT_DHCP

want_d2 = d2
want_dhcp4 = dhcp4
want_dhcp6 = dhcp6

endif # WANT_DHCP

if WANT_DNS

want_auth = auth
want_dbutil = dbutil
want_ddns = ddns
want_loadzone = loadzone
want_xfrin = xfrin
want_xfrout = xfrout
want_zonemgr = zonemgr

if WANT_EXPERIMENTAL_RESOLVER
want_resolver = resolver
endif

if USE_SHARED_MEMORY
# Build the memory manager only if we have shared memory.
# It is useless without it.
want_memmgr = memmgr
endif

endif # WANT_DNS

# The following build order must be maintained. So we create the
# variables above and add directories in that order to SUBDIRS.
SUBDIRS = bind10 bindctl cfgmgr $(want_ddns) $(want_loadzone) msgq cmdctl \
	$(want_auth) $(want_xfrin) $(want_xfrout) usermgr $(want_zonemgr) \
	stats tests $(want_resolver) sockcreator $(want_dhcp4) $(want_dhcp6) \
	$(want_d2) $(want_dbutil) sysinfo $(want_memmgr)

check-recursive: all-recursive
