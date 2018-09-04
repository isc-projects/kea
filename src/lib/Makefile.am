# The following build order must be maintained.
SUBDIRS = exceptions util log cryptolink dns asiolink cc database

if HAVE_MYSQL
SUBDIRS += mysql
endif

if HAVE_PGSQL
SUBDIRS += pgsql
endif

if HAVE_CQL
SUBDIRS += cql
endif

SUBDIRS += testutils hooks dhcp config stats asiodns dhcp_ddns eval \
	dhcpsrv cfgrpt \
	process http
