# The following build order must be maintained.
SUBDIRS = exceptions util log cryptolink dns asiolink cc testutils hooks dhcp \
          config stats

if HAVE_SYSREPO
SUBDIRS += yang
endif

SUBDIRS += asiodns dhcp_ddns eval dhcpsrv cfgrpt process http
