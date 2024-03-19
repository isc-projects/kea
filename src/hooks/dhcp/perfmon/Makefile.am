SUBDIRS = . libloadtests tests

AM_CPPFLAGS  = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS  = $(KEA_CXXFLAGS)

# Ensure that the message file and doxygen file is included in the distribution
EXTRA_DIST = perfmon_messages.mes
EXTRA_DIST += perfmon.dox

CLEANFILES = *.gcno *.gcda

# convenience archive

noinst_LTLIBRARIES = libperfmon.la

libperfmon_la_SOURCES = perfmon_callouts.cc
libperfmon_la_SOURCES += perfmon_log.cc perfmon_log.h
libperfmon_la_SOURCES += perfmon_messages.cc perfmon_messages.h
libperfmon_la_SOURCES += monitored_duration.cc monitored_duration.h
libperfmon_la_SOURCES += alarm.cc alarm.h
libperfmon_la_SOURCES += monitored_duration_store.cc monitored_duration_store.h
libperfmon_la_SOURCES += alarm_store.cc alarm_store.h
libperfmon_la_SOURCES += perfmon_config.cc perfmon_config.h
libperfmon_la_SOURCES += perfmon_mgr.cc perfmon_mgr.h
libperfmon_la_SOURCES += version.cc

libperfmon_la_CXXFLAGS = $(AM_CXXFLAGS)
libperfmon_la_CPPFLAGS = $(AM_CPPFLAGS)

# install the shared object into $(libdir)/kea/hooks
lib_hooksdir = $(libdir)/kea/hooks
lib_hooks_LTLIBRARIES = libdhcp_perfmon.la

libdhcp_perfmon_la_SOURCES =
libdhcp_perfmon_la_LDFLAGS  = $(AM_LDFLAGS)
libdhcp_perfmon_la_LDFLAGS += -avoid-version -export-dynamic -module
libdhcp_perfmon_la_LIBADD  = libperfmon.la
libdhcp_perfmon_la_LIBADD += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
libdhcp_perfmon_la_LIBADD += $(top_builddir)/src/lib/process/libkea-process.la
libdhcp_perfmon_la_LIBADD += $(top_builddir)/src/lib/eval/libkea-eval.la
libdhcp_perfmon_la_LIBADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
libdhcp_perfmon_la_LIBADD += $(top_builddir)/src/lib/stats/libkea-stats.la
libdhcp_perfmon_la_LIBADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
libdhcp_perfmon_la_LIBADD += $(top_builddir)/src/lib/http/libkea-http.la
libdhcp_perfmon_la_LIBADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
libdhcp_perfmon_la_LIBADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
libdhcp_perfmon_la_LIBADD += $(top_builddir)/src/lib/database/libkea-database.la
libdhcp_perfmon_la_LIBADD += $(top_builddir)/src/lib/cc/libkea-cc.la
libdhcp_perfmon_la_LIBADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libdhcp_perfmon_la_LIBADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
libdhcp_perfmon_la_LIBADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
libdhcp_perfmon_la_LIBADD += $(top_builddir)/src/lib/log/libkea-log.la
libdhcp_perfmon_la_LIBADD += $(top_builddir)/src/lib/util/libkea-util.la
libdhcp_perfmon_la_LIBADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libdhcp_perfmon_la_LIBADD += $(LOG4CPLUS_LIBS)
libdhcp_perfmon_la_LIBADD += $(CRYPTO_LIBS)
libdhcp_perfmon_la_LIBADD += $(BOOST_LIBS)

# If we want to get rid of all generated messages files, we need to use
# make maintainer-clean. The proper way to introduce custom commands for
# that operation is to define maintainer-clean-local target. However,
# make maintainer-clean also removes Makefile, so running configure script
# is required.  To make it easy to rebuild messages without going through
# reconfigure, a new target messages-clean has been added.
maintainer-clean-local:
	rm -f perfmon_messages.h perfmon_messages.cc

# To regenerate messages files, one can do:
#
# make messages-clean
# make messages
#
# This is needed only when a .mes file is modified.
messages-clean: maintainer-clean-local

if GENERATE_MESSAGES

# Define rule to build logging source files from message file
messages: perfmon_messages.h perfmon_messages.cc
	@echo Message files regenerated

perfmon_messages.h perfmon_messages.cc: perfmon_messages.mes
	$(top_builddir)/src/lib/log/compiler/kea-msg-compiler $(top_srcdir)/src/hooks/dhcp/perfmon/perfmon_messages.mes

else

messages perfmon_messages.h perfmon_messages.cc:
	@echo Messages generation disabled. Configure with --enable-generate-messages to enable it.

endif

