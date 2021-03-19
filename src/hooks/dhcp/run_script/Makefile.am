SUBDIRS = . libloadtests tests

AM_CPPFLAGS  = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS  = $(KEA_CXXFLAGS)

# Ensure that the message file and doxygen file is included in the distribution
EXTRA_DIST = run_script_messages.mes
EXTRA_DIST += run_script.dox

CLEANFILES = *.gcno *.gcda

# convenience archive

noinst_LTLIBRARIES = librun_script.la

librun_script_la_SOURCES  = run_script_callouts.cc
librun_script_la_SOURCES += run_script.cc run_script.h
librun_script_la_SOURCES += run_script_log.cc run_script_log.h
librun_script_la_SOURCES += run_script_messages.cc run_script_messages.h
librun_script_la_SOURCES += version.cc

librun_script_la_CXXFLAGS = $(AM_CXXFLAGS)
librun_script_la_CPPFLAGS = $(AM_CPPFLAGS)

# install the shared object into $(libdir)/kea/hooks
lib_hooksdir = $(libdir)/kea/hooks
lib_hooks_LTLIBRARIES = libdhcp_run_script.la

libdhcp_run_script_la_SOURCES  =
libdhcp_run_script_la_LDFLAGS  = $(AM_LDFLAGS)
libdhcp_run_script_la_LDFLAGS  += -avoid-version -export-dynamic -module
libdhcp_run_script_la_LIBADD  = librun_script.la
libdhcp_run_script_la_LIBADD += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
libdhcp_run_script_la_LIBADD += $(top_builddir)/src/lib/process/libkea-process.la
libdhcp_run_script_la_LIBADD += $(top_builddir)/src/lib/eval/libkea-eval.la
libdhcp_run_script_la_LIBADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
libdhcp_run_script_la_LIBADD += $(top_builddir)/src/lib/stats/libkea-stats.la
libdhcp_run_script_la_LIBADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
libdhcp_run_script_la_LIBADD += $(top_builddir)/src/lib/http/libkea-http.la
libdhcp_run_script_la_LIBADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
libdhcp_run_script_la_LIBADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
libdhcp_run_script_la_LIBADD += $(top_builddir)/src/lib/database/libkea-database.la
libdhcp_run_script_la_LIBADD += $(top_builddir)/src/lib/cc/libkea-cc.la
libdhcp_run_script_la_LIBADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libdhcp_run_script_la_LIBADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
libdhcp_run_script_la_LIBADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
libdhcp_run_script_la_LIBADD += $(top_builddir)/src/lib/log/libkea-log.la
libdhcp_run_script_la_LIBADD += $(top_builddir)/src/lib/util/libkea-util.la
libdhcp_run_script_la_LIBADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libdhcp_run_script_la_LIBADD += $(LOG4CPLUS_LIBS)
libdhcp_run_script_la_LIBADD += $(CRYPTO_LIBS)
libdhcp_run_script_la_LIBADD += $(BOOST_LIBS)

# If we want to get rid of all generated messages files, we need to use
# make maintainer-clean. The proper way to introduce custom commands for
# that operation is to define maintainer-clean-local target. However,
# make maintainer-clean also removes Makefile, so running configure script
# is required.  To make it easy to rebuild messages without going through
# reconfigure, a new target messages-clean has been added.
maintainer-clean-local:
	rm -f run_script_messages.h run_script_messages.cc

# To regenerate messages files, one can do:
#
# make messages-clean
# make messages
#
# This is needed only when a .mes file is modified.
messages-clean: maintainer-clean-local

if GENERATE_MESSAGES

# Define rule to build logging source files from message file
messages: run_script_messages.h run_script_messages.cc
	@echo Message files regenerated

run_script_messages.h run_script_messages.cc: run_script_messages.mes
	$(top_builddir)/src/lib/log/compiler/kea-msg-compiler $(top_srcdir)/src/hooks/dhcp/run_script/run_script_messages.mes

else

messages run_script_messages.h run_script_messages.cc:
	@echo Messages generation disabled. Configure with --enable-generate-messages to enable it.

endif

