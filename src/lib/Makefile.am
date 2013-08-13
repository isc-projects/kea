if BUILD_EXPERIMENTAL_RESOLVER
# Build resolver only with --enable-experimental-resolver
experimental_resolver = resolve
endif

SUBDIRS = exceptions util log hooks cryptolink dns cc config acl xfr bench \
          asiolink asiodns nsas cache $(experimental_resolver) testutils \
          datasrc server_common python dhcp dhcp_ddns dhcpsrv statistics
