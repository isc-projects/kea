SUBDIRS = . tests

AM_CPPFLAGS  = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS  = $(KEA_CXXFLAGS)

# Define rule to build logging source files from message file
stat_cmds_messages.h stat_cmds_messages.cc: s-messages
s-messages: stat_cmds_messages.mes
	$(top_builddir)/src/lib/log/compiler/kea-msg-compiler $(top_srcdir)/src/hooks/dhcp/stat_cmds/stat_cmds_messages.mes
	touch $@

# Tell automake that the message files are built as part of the build process
# (so that they are built before the main library is built).
BUILT_SOURCES = stat_cmds_messages.h stat_cmds_messages.cc

# Ensure that the message file and doxygen file is included in the distribution
EXTRA_DIST = stat_cmds_messages.mes
EXTRA_DIST += stat_cmds.dox

# Get rid of generated message files on a clean
CLEANFILES = *.gcno *.gcda stat_cmds_messages.h stat_cmds_messages.cc s-messages

# convenience archive

noinst_LTLIBRARIES = libstat_cmds.la

libstat_cmds_la_SOURCES  = stat_cmds.cc stat_cmds.h
libstat_cmds_la_SOURCES += stat_cmds_callouts.cc
libstat_cmds_la_SOURCES += stat_cmds_log.cc stat_cmds_log.h
libstat_cmds_la_SOURCES += version.cc

nodist_libstat_cmds_la_SOURCES = stat_cmds_messages.cc stat_cmds_messages.h

libstat_cmds_la_CXXFLAGS = $(AM_CXXFLAGS)
libstat_cmds_la_CPPFLAGS = $(AM_CPPFLAGS)

# install the shared object into $(libdir)/hooks
lib_hooksdir = $(libdir)/hooks
lib_hooks_LTLIBRARIES = libdhcp_stat_cmds.la

libdhcp_stat_cmds_la_SOURCES  =
libdhcp_stat_cmds_la_LDFLAGS  = $(AM_LDFLAGS)
libdhcp_stat_cmds_la_LDFLAGS  += -avoid-version -export-dynamic -module
libdhcp_stat_cmds_la_LIBADD  = libstat_cmds.la
libdhcp_stat_cmds_la_LIBADD  += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
libdhcp_stat_cmds_la_LIBADD  += $(top_builddir)/src/lib/config/libkea-cfgclient.la
libdhcp_stat_cmds_la_LIBADD  += $(top_builddir)/src/lib/cc/libkea-cc.la
libdhcp_stat_cmds_la_LIBADD  += $(top_builddir)/src/lib/hooks/libkea-hooks.la
libdhcp_stat_cmds_la_LIBADD  += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libdhcp_stat_cmds_la_LIBADD  += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
libdhcp_stat_cmds_la_LIBADD  += $(top_builddir)/src/lib/eval/libkea-eval.la
libdhcp_stat_cmds_la_LIBADD  += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
libdhcp_stat_cmds_la_LIBADD  += $(top_builddir)/src/lib/stats/libkea-stats.la
libdhcp_stat_cmds_la_LIBADD  += $(top_builddir)/src/lib/dns/libkea-dns++.la
libdhcp_stat_cmds_la_LIBADD  += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
libdhcp_stat_cmds_la_LIBADD  += $(top_builddir)/src/lib/log/libkea-log.la
libdhcp_stat_cmds_la_LIBADD  += $(top_builddir)/src/lib/util/threads/libkea-threads.la
libdhcp_stat_cmds_la_LIBADD  += $(top_builddir)/src/lib/util/libkea-util.la
libdhcp_stat_cmds_la_LIBADD  += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libdhcp_stat_cmds_la_LIBADD  += $(LOG4CPLUS_LIBS)
libdhcp_stat_cmds_la_LIBADD  += $(CRYPTO_LIBS)
libdhcp_stat_cmds_la_LIBADD  += $(BOOST_LIBS)
