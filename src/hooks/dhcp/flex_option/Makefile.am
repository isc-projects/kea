SUBDIRS = . libloadtests tests

AM_CPPFLAGS  = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS  = $(KEA_CXXFLAGS)

# Ensure that the message file and doxygen file is included in the distribution
EXTRA_DIST = flex_option_messages.mes
EXTRA_DIST += flex_option.dox

CLEANFILES = *.gcno *.gcda

# convenience archive

noinst_LTLIBRARIES = libflex_option.la

libflex_option_la_SOURCES  = flex_option.cc flex_option.h
libflex_option_la_SOURCES += flex_option_callouts.cc
libflex_option_la_SOURCES += flex_option_log.cc flex_option_log.h
libflex_option_la_SOURCES += flex_option_messages.cc flex_option_messages.h
libflex_option_la_SOURCES += version.cc

libflex_option_la_CXXFLAGS = $(AM_CXXFLAGS)
libflex_option_la_CPPFLAGS = $(AM_CPPFLAGS)

# install the shared object into $(libdir)/kea/hooks
lib_hooksdir = $(libdir)/kea/hooks
lib_hooks_LTLIBRARIES = libdhcp_flex_option.la

libdhcp_flex_option_la_SOURCES  =
libdhcp_flex_option_la_LDFLAGS  = $(AM_LDFLAGS)
libdhcp_flex_option_la_LDFLAGS  += -avoid-version -export-dynamic -module
libdhcp_flex_option_la_LIBADD = libflex_option.la
libdhcp_flex_option_la_LIBADD += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
libdhcp_flex_option_la_LIBADD += $(top_builddir)/src/lib/process/libkea-process.la
libdhcp_flex_option_la_LIBADD += $(top_builddir)/src/lib/eval/libkea-eval.la
libdhcp_flex_option_la_LIBADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
libdhcp_flex_option_la_LIBADD += $(top_builddir)/src/lib/stats/libkea-stats.la
libdhcp_flex_option_la_LIBADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
libdhcp_flex_option_la_LIBADD += $(top_builddir)/src/lib/http/libkea-http.la
libdhcp_flex_option_la_LIBADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
libdhcp_flex_option_la_LIBADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
libdhcp_flex_option_la_LIBADD += $(top_builddir)/src/lib/database/libkea-database.la
libdhcp_flex_option_la_LIBADD += $(top_builddir)/src/lib/cc/libkea-cc.la
libdhcp_flex_option_la_LIBADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libdhcp_flex_option_la_LIBADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
libdhcp_flex_option_la_LIBADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
libdhcp_flex_option_la_LIBADD += $(top_builddir)/src/lib/log/libkea-log.la
libdhcp_flex_option_la_LIBADD += $(top_builddir)/src/lib/util/libkea-util.la
libdhcp_flex_option_la_LIBADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libdhcp_flex_option_la_LIBADD += $(LOG4CPLUS_LIBS)
libdhcp_flex_option_la_LIBADD += $(CRYPTO_LIBS)
libdhcp_flex_option_la_LIBADD += $(BOOST_LIBS)

# If we want to get rid of all generated messages files, we need to use
# make maintainer-clean. The proper way to introduce custom commands for
# that operation is to define maintainer-clean-local target. However,
# make maintainer-clean also removes Makefile, so running configure script
# is required.  To make it easy to rebuild messages without going through
# reconfigure, a new target messages-clean has been added.
maintainer-clean-local:
	rm -f flex_option_messages.h flex_option_messages.cc

# To regenerate messages files, one can do:
#
# make messages-clean
# make messages
#
# This is needed only when a .mes file is modified.
messages-clean: maintainer-clean-local

if GENERATE_MESSAGES

# Define rule to build logging source files from message file
messages: flex_option_messages.h flex_option_messages.cc
	@echo Message files regenerated

flex_option_messages.h flex_option_messages.cc: flex_option_messages.mes
	$(top_builddir)/src/lib/log/compiler/kea-msg-compiler $(top_srcdir)/src/hooks/dhcp/flex_option/flex_option_messages.mes

else

messages flex_option_messages.h flex_option_messages.cc:
	@echo Messages generation disabled. Configure with --enable-generate-messages to enable it.

endif

