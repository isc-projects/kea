SUBDIRS = . testutils tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(KEA_CXXFLAGS)

EXTRA_DIST  =

CLEANFILES = *.gcno *.gcda

lib_LTLIBRARIES = libkea-d2srv.la
libkea_d2srv_la_SOURCES  =
libkea_d2srv_la_SOURCES += d2_cfg_mgr.cc d2_cfg_mgr.h
libkea_d2srv_la_SOURCES += d2_config.cc d2_config.h
libkea_d2srv_la_SOURCES += d2_log.cc d2_log.h
libkea_d2srv_la_SOURCES += d2_messages.cc d2_messages.h
libkea_d2srv_la_SOURCES += d2_update_message.cc d2_update_message.h
libkea_d2srv_la_SOURCES += d2_simple_parser.cc d2_simple_parser.h
libkea_d2srv_la_SOURCES += d2_stats.cc d2_stats.h
libkea_d2srv_la_SOURCES += d2_tsig_key.cc d2_tsig_key.h
libkea_d2srv_la_SOURCES += d2_zone.cc d2_zone.h
libkea_d2srv_la_SOURCES += dns_client.cc dns_client.h
libkea_d2srv_la_SOURCES += nc_trans.cc nc_trans.h
EXTRA_DIST += d2srv.dox d2_messages.mes

libkea_d2srv_la_CXXFLAGS = $(AM_CXXFLAGS)
libkea_d2srv_la_CPPFLAGS = $(AM_CPPFLAGS)

libkea_d2srv_la_LIBADD  =
libkea_d2srv_la_LIBADD += $(top_builddir)/src/lib/process/libkea-process.la
libkea_d2srv_la_LIBADD += $(top_builddir)/src/lib/cfgrpt/libcfgrpt.la
libkea_d2srv_la_LIBADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
libkea_d2srv_la_LIBADD += $(top_builddir)/src/lib/asiodns/libkea-asiodns.la
libkea_d2srv_la_LIBADD += $(top_builddir)/src/lib/stats/libkea-stats.la
libkea_d2srv_la_LIBADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
libkea_d2srv_la_LIBADD += $(top_builddir)/src/lib/http/libkea-http.la
libkea_d2srv_la_LIBADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
libkea_d2srv_la_LIBADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
libkea_d2srv_la_LIBADD += $(top_builddir)/src/lib/database/libkea-database.la
libkea_d2srv_la_LIBADD += $(top_builddir)/src/lib/cc/libkea-cc.la
libkea_d2srv_la_LIBADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libkea_d2srv_la_LIBADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
libkea_d2srv_la_LIBADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
libkea_d2srv_la_LIBADD += $(top_builddir)/src/lib/log/libkea-log.la
libkea_d2srv_la_LIBADD += $(top_builddir)/src/lib/util/libkea-util.la
libkea_d2srv_la_LIBADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libkea_d2srv_la_LIBADD += $(LOG4CPLUS_LIBS) $(CRYPTO_LIBS) $(BOOST_LIBS)

libkea_d2srv_la_LDFLAGS  = -no-undefined -version-info 4:0:0
libkea_d2srv_la_LDFLAGS += $(AM_LDFLAGS) $(CRYPTO_LDFLAGS)

# If we want to get rid of all generated messages files, we need to use
# make maintainer-clean. The proper way to introduce custom commands for
# that operation is to define maintainer-clean-local target. However,
# make maintainer-clean also removes Makefile, so running configure script
# is required.  To make it easy to rebuild messages without going through
# reconfigure, a new target messages-clean has been added.
maintainer-clean-local:
	rm -f d2_messages.h d2_messages.cc

# To regenerate messages files, one can do:
#
# make messages-clean
# make messages
#
# This is needed only when a .mes file is modified.
messages-clean: maintainer-clean-local

if GENERATE_MESSAGES

# Define rule to build logging source files from message file
messages: d2_messages.h d2_messages.cc
	@echo Message files regenerated

d2_messages.h d2_messages.cc: d2_messages.mes
	$(top_builddir)/src/lib/log/compiler/kea-msg-compiler $(top_srcdir)/src/lib/d2srv/d2_messages.mes

else

messages d2_messages.h d2_messages.cc:
	@echo Messages generation disabled. Configure with --enable-generate-messages to enable it.

endif

# Specify the headers for copying into the installation directory tree.
libkea_d2srv_includedir = $(pkgincludedir)/d2srv
libkea_d2srv_include_HEADERS = \
	d2_cfg_mgr.h \
	d2_config.h \
	d2_log.h \
	d2_messages.h \
	d2_simple_parser.h
