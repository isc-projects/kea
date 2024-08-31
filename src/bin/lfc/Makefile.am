SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/bin -I$(top_builddir)/src/bin
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

EXTRA_DIST = lfc.dox


# convenience archive

noinst_LTLIBRARIES = liblfc.la

liblfc_la_SOURCES  =
liblfc_la_SOURCES += lfc_controller.h lfc_controller.cc
liblfc_la_SOURCES += lfc_log.h lfc_log.cc
liblfc_la_SOURCES += lfc_messages.h lfc_messages.cc
EXTRA_DIST += lfc_messages.mes

sbin_PROGRAMS = kea-lfc

kea_lfc_SOURCES  = main.cc

kea_lfc_LDADD  = liblfc.la
kea_lfc_LDADD += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
kea_lfc_LDADD += $(top_builddir)/src/lib/process/libkea-process.la
kea_lfc_LDADD += $(top_builddir)/src/lib/eval/libkea-eval.la
kea_lfc_LDADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
kea_lfc_LDADD += $(top_builddir)/src/lib/stats/libkea-stats.la
kea_lfc_LDADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
kea_lfc_LDADD += $(top_builddir)/src/lib/http/libkea-http.la
kea_lfc_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
kea_lfc_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la

if HAVE_PGSQL
kea_lfc_LDADD += $(top_builddir)/src/lib/pgsql/libkea-pgsql.la
endif

if HAVE_MYSQL
kea_lfc_LDADD += $(top_builddir)/src/lib/mysql/libkea-mysql.la
endif

kea_lfc_LDADD += $(top_builddir)/src/lib/database/libkea-database.la
kea_lfc_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
kea_lfc_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
kea_lfc_LDADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
kea_lfc_LDADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
kea_lfc_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
kea_lfc_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
kea_lfc_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
kea_lfc_LDADD += $(LOG4CPLUS_LIBS) $(CRYPTO_LIBS) $(BOOST_LIBS)

kea_lfc_LDFLAGS = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS)
if HAVE_MYSQL
kea_lfc_LDFLAGS += $(MYSQL_LIBS)
endif
if HAVE_PGSQL
kea_lfc_LDFLAGS += $(PGSQL_LIBS)
endif

kea_lfcdir = $(pkgdatadir)

# If we want to get rid of all generated messages files, we need to use
# make maintainer-clean. The proper way to introduce custom commands for
# that operation is to define maintainer-clean-local target. However,
# make maintainer-clean also removes Makefile, so running configure script
# is required.  To make it easy to rebuild messages without going through
# reconfigure, a new target messages-clean has been added.
maintainer-clean-local:
	rm -f lfc_messages.h lfc_messages.cc

# To regenerate messages files, one can do:
#
# make messages-clean
# make messages
#
# This is needed only when a .mes file is modified.
messages-clean: maintainer-clean-local

if GENERATE_MESSAGES

# Define rule to build logging source files from message file
messages: lfc_messages.h lfc_messages.cc
	@echo Message files regenerated

lfc_messages.h lfc_messages.cc: lfc_messages.mes
	$(top_builddir)/src/lib/log/compiler/kea-msg-compiler $(top_srcdir)/src/bin/lfc/lfc_messages.mes

else

messages lfc_messages.h lfc_messages.cc:
	@echo Messages generation disabled. Configure with --enable-generate-messages to enable it.

endif
