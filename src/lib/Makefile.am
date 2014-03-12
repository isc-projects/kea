if WANT_DHCP

want_dhcp = dhcp
want_dhcp_ddns = dhcp_ddns
want_dhcpsrv = dhcpsrv
want_hooks = hooks

endif # WANT_DHCP

if WANT_DNS

want_acl = acl
want_bench = bench
want_datasrc = datasrc
want_nsas = nsas
want_server_common = server_common
want_statistics = statistics
want_xfr = xfr

if WANT_EXPERIMENTAL_RESOLVER
want_cache = cache
want_resolve = resolve
endif

endif # WANT_DNS

# The following build order must be maintained. So we create the
# variables above and add directories in that order to SUBDIRS.
SUBDIRS = exceptions util log $(want_hooks) cryptolink dns cc config \
          $(want_acl) $(want_xfr) $(want_bench) asiolink asiodns \
          $(want_nsas) $(want_cache) $(want_resolve) testutils \
          $(want_datasrc) $(want_server_common) python $(want_dhcp) \
          $(want_dhcp_ddns) $(want_dhcpsrv) $(want_statistics)
