SUBDIRS = . tests

AM_CPPFLAGS  = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS  = $(KEA_CXXFLAGS)

# Define rule to build logging source files from message file
lease_cmds_messages.h lease_cmds_messages.cc: s-messages
s-messages: lease_cmds_messages.mes
	$(top_builddir)/src/lib/log/compiler/kea-msg-compiler $(top_srcdir)/src/hooks/dhcp/lease_cmds/lease_cmds_messages.mes
	touch $@

# Tell automake that the message files are built as part of the build process
# (so that they are built before the main library is built).
BUILT_SOURCES = lease_cmds_messages.h lease_cmds_messages.cc

# Ensure that the message file and doxygen file is included in the distribution
EXTRA_DIST = lease_cmds_messages.mes
EXTRA_DIST += lease_cmds.dox

# Get rid of generated message files on a clean
CLEANFILES = *.gcno *.gcda lease_cmds_messages.h lease_cmds_messages.cc s-messages

# convenience archive

noinst_LTLIBRARIES = liblease_cmds.la

liblease_cmds_la_SOURCES  = lease_cmds.cc lease_cmds.h
liblease_cmds_la_SOURCES += lease_cmds_callouts.cc
liblease_cmds_la_SOURCES += lease_parser.h lease_parser.cc
liblease_cmds_la_SOURCES += lease_cmds_log.cc lease_cmds_log.h
liblease_cmds_la_SOURCES += version.cc

nodist_liblease_cmds_la_SOURCES = lease_cmds_messages.cc lease_cmds_messages.h

liblease_cmds_la_CXXFLAGS = $(AM_CXXFLAGS)
liblease_cmds_la_CPPFLAGS = $(AM_CPPFLAGS)

# install the shared object into $(libdir)/hooks
lib_hooksdir = $(libdir)/hooks
lib_hooks_LTLIBRARIES = libdhcp_lease_cmds.la

libdhcp_lease_cmds_la_SOURCES  =
libdhcp_lease_cmds_la_LDFLAGS  = $(AM_LDFLAGS)
libdhcp_lease_cmds_la_LDFLAGS  += -avoid-version -export-dynamic -module
libdhcp_lease_cmds_la_LIBADD  = liblease_cmds.la
libdhcp_lease_cmds_la_LIBADD  += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
libdhcp_lease_cmds_la_LIBADD  += $(top_builddir)/src/lib/config/libkea-cfgclient.la
libdhcp_lease_cmds_la_LIBADD  += $(top_builddir)/src/lib/cc/libkea-cc.la
libdhcp_lease_cmds_la_LIBADD  += $(top_builddir)/src/lib/hooks/libkea-hooks.la
libdhcp_lease_cmds_la_LIBADD  += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libdhcp_lease_cmds_la_LIBADD  += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
libdhcp_lease_cmds_la_LIBADD  += $(top_builddir)/src/lib/eval/libkea-eval.la
libdhcp_lease_cmds_la_LIBADD  += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
libdhcp_lease_cmds_la_LIBADD  += $(top_builddir)/src/lib/stats/libkea-stats.la
libdhcp_lease_cmds_la_LIBADD  += $(top_builddir)/src/lib/dns/libkea-dns++.la
libdhcp_lease_cmds_la_LIBADD  += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
libdhcp_lease_cmds_la_LIBADD  += $(top_builddir)/src/lib/log/libkea-log.la
libdhcp_lease_cmds_la_LIBADD  += $(top_builddir)/src/lib/util/threads/libkea-threads.la
libdhcp_lease_cmds_la_LIBADD  += $(top_builddir)/src/lib/util/libkea-util.la
libdhcp_lease_cmds_la_LIBADD  += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libdhcp_lease_cmds_la_LIBADD  += $(LOG4CPLUS_LIBS)
libdhcp_lease_cmds_la_LIBADD  += $(CRYPTO_LIBS)
libdhcp_lease_cmds_la_LIBADD  += $(BOOST_LIBS)
