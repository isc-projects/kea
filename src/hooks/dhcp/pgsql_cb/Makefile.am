SUBDIRS = . tests

AM_CPPFLAGS  = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES) $(PGSQL_CPPFLAGS)
AM_CXXFLAGS  = $(KEA_CXXFLAGS)

# Ensure that the message file is included in the distribution
EXTRA_DIST = pgsql_cb_messages.mes

CLEANFILES = *.gcno *.gcda

# convenience archive

noinst_LTLIBRARIES = libpgsqlcb.la
 	
libpgsqlcb_la_SOURCES  = pgsql_cb_callouts.cc

# Commented out for now - see kea#95
libpgsqlcb_la_SOURCES += pgsql_cb_dhcp4.cc pgsql_cb_dhcp4.h

# Commented out for now - to be added back in #96
libpgsqlcb_la_SOURCES += pgsql_cb_dhcp6.cc pgsql_cb_dhcp6.h

libpgsqlcb_la_SOURCES += pgsql_cb_impl.cc pgsql_cb_impl.h
libpgsqlcb_la_SOURCES += pgsql_cb_messages.cc pgsql_cb_messages.h
libpgsqlcb_la_SOURCES += pgsql_cb_log.cc pgsql_cb_log.h
libpgsqlcb_la_SOURCES += pgsql_query_macros_dhcp.h
libpgsqlcb_la_SOURCES += version.cc

libpgsqlcb_la_CXXFLAGS = $(AM_CXXFLAGS)
libpgsqlcb_la_CPPFLAGS = $(AM_CPPFLAGS)

# install the shared object into $(libdir)/kea/hooks
lib_hooksdir = $(libdir)/kea/hooks
lib_hooks_LTLIBRARIES = libdhcp_pgsql_cb.la

libdhcp_pgsql_cb_la_SOURCES  =
libdhcp_pgsql_cb_la_LDFLAGS  = $(AM_LDFLAGS) $(pgsql_LIBS)
libdhcp_pgsql_cb_la_LDFLAGS  += -avoid-version -export-dynamic -module

libdhcp_pgsql_cb_la_LIBADD  = libpgsqlcb.la
libdhcp_pgsql_cb_la_LIBADD += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
libdhcp_pgsql_cb_la_LIBADD += $(top_builddir)/src/lib/eval/libkea-eval.la
libdhcp_pgsql_cb_la_LIBADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
libdhcp_pgsql_cb_la_LIBADD += $(top_builddir)/src/lib/process/libkea-process.la
libdhcp_pgsql_cb_la_LIBADD += $(top_builddir)/src/lib/stats/libkea-stats.la
libdhcp_pgsql_cb_la_LIBADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
libdhcp_pgsql_cb_la_LIBADD += $(top_builddir)/src/lib/http/libkea-http.la
libdhcp_pgsql_cb_la_LIBADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
libdhcp_pgsql_cb_la_LIBADD += $(top_builddir)/src/lib/pgsql/libkea-pgsql.la
libdhcp_pgsql_cb_la_LIBADD += $(top_builddir)/src/lib/database/libkea-database.la
libdhcp_pgsql_cb_la_LIBADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libdhcp_pgsql_cb_la_LIBADD += $(top_builddir)/src/lib/cc/libkea-cc.la
libdhcp_pgsql_cb_la_LIBADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
libdhcp_pgsql_cb_la_LIBADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
libdhcp_pgsql_cb_la_LIBADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
libdhcp_pgsql_cb_la_LIBADD += $(top_builddir)/src/lib/log/libkea-log.la
libdhcp_pgsql_cb_la_LIBADD += $(top_builddir)/src/lib/util/libkea-util.la
libdhcp_pgsql_cb_la_LIBADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la

# If we want to get rid of all generated messages files, we need to use
# make maintainer-clean. The proper way to introduce custom commands for
# that operation is to define maintainer-clean-local target. However,
# make maintainer-clean also removes Makefile, so running configure script
# is required.  To make it easy to rebuild messages without going through
# reconfigure, a new target messages-clean has been added.
maintainer-clean-local:
	rm -f pgsql_cb_messages.h pgsql_cb_messages.cc

# To regenerate messages files, one can do:
#
# make messages-clean
# make messages
#
# This is needed only when a .mes file is modified.
messages-clean: maintainer-clean-local

if GENERATE_MESSAGES

# Define rule to build logging source files from message file
messages: pgsql_cb_messages.h pgsql_cb_messages.cc
	@echo Message files regenerated

pgsql_cb_messages.h pgsql_cb_messages.cc: pgsql_cb_messages.mes
	$(top_builddir)/src/lib/log/compiler/kea-msg-compiler $(top_srcdir)/src/hooks/dhcp/pgsql_cb/pgsql_cb_messages.mes

else

messages pgsql_cb_messages.h pgsql_cb_messages.cc:
	@echo Messages generation disabled. Configure with --enable-generate-messages to enable it.

endif
