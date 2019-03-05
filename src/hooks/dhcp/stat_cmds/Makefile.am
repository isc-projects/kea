SUBDIRS = . tests

AM_CPPFLAGS  = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS  = $(KEA_CXXFLAGS)

# Ensure that the message file and doxygen file is included in the distribution
EXTRA_DIST = stat_cmds_messages.mes
EXTRA_DIST += stat_cmds.dox

CLEANFILES = *.gcno *.gcda

# convenience archive

noinst_LTLIBRARIES = libstat_cmds.la

libstat_cmds_la_SOURCES  = stat_cmds.cc stat_cmds.h
libstat_cmds_la_SOURCES += stat_cmds_callouts.cc
libstat_cmds_la_SOURCES += stat_cmds_log.cc stat_cmds_log.h
libstat_cmds_la_SOURCES += stat_cmds_messages.cc stat_cmds_messages.h
libstat_cmds_la_SOURCES += version.cc

libstat_cmds_la_CXXFLAGS = $(AM_CXXFLAGS)
libstat_cmds_la_CPPFLAGS = $(AM_CPPFLAGS)

# install the shared object into $(libdir)/kea/hooks
lib_hooksdir = $(libdir)/kea/hooks
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

# If we want to get rid of all generated messages files, we need to use
# make maintainer-clean. The proper way to introduce custom commands for
# that operation is to define maintainer-clean-local target. However,
# make maintainer-clean also removes Makefile, so running configure script
# is required.  To make it easy to rebuild messages without going through
# reconfigure, a new target messages-clean has been added.
maintainer-clean-local:
	rm -f stat_cmds_messages.h stat_cmds_messages.cc

# To regenerate messages files, one can do:
#
# make messages-clean
# make messages
#
# This is needed only when a .mes file is modified.
messages-clean: maintainer-clean-local

if GENERATE_MESSAGES

# Define rule to build logging source files from message file
messages: stat_cmds_messages.h stat_cmds_messages.cc
	@echo Message files regenerated

stat_cmds_messages.h stat_cmds_messages.cc: stat_cmds_messages.mes
	$(top_builddir)/src/lib/log/compiler/kea-msg-compiler $(top_srcdir)/src/hooks/dhcp/stat_cmds/stat_cmds_messages.mes

else

messages stat_cmds_messages.h stat_cmds_messages.cc:
	@echo Messages generation disabled. Configure with --enable-generate-messages to enable it.

endif

