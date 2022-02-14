SUBDIRS = . libloadtests tests

AM_CPPFLAGS  = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS  = $(KEA_CXXFLAGS)

HOOK_NAME=ddns_tuning

# Ensure that the message file and doxygen file is included in the distribution
EXTRA_DIST = $(HOOK_NAME)_messages.mes
EXTRA_DIST += $(HOOK_NAME).dox

CLEANFILES = *.gcno *.gcda

# convenience archive

noinst_LTLIBRARIES = libddns_tuning.la

libddns_tuning_la_SOURCES  = $(HOOK_NAME).cc $(HOOK_NAME).h
libddns_tuning_la_SOURCES += $(HOOK_NAME)_callouts.cc
libddns_tuning_la_SOURCES += $(HOOK_NAME)_log.cc $(HOOK_NAME)_log.h
libddns_tuning_la_SOURCES += $(HOOK_NAME)_messages.cc $(HOOK_NAME)_messages.h
libddns_tuning_la_SOURCES += version.cc

ddns_tuning_la_CXXFLAGS = $(AM_CXXFLAGS)
ddns_tuning_la_CPPFLAGS = $(AM_CPPFLAGS)

# install the shared object into $(libdir)/kea/hooks
lib_hooksdir = $(libdir)/kea/hooks
lib_hooks_LTLIBRARIES = libdhcp_ddns_tuning.la

libdhcp_ddns_tuning_la_SOURCES  =
libdhcp_ddns_tuning_la_LDFLAGS  = $(AM_LDFLAGS)
libdhcp_ddns_tuning_la_LDFLAGS  += -avoid-version -export-dynamic -module
libdhcp_ddns_tuning_la_LIBADD = lib$(HOOK_NAME).la
libdhcp_ddns_tuning_la_LIBADD += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
libdhcp_ddns_tuning_la_LIBADD += $(top_builddir)/src/lib/process/libkea-process.la
libdhcp_ddns_tuning_la_LIBADD += $(top_builddir)/src/lib/eval/libkea-eval.la
libdhcp_ddns_tuning_la_LIBADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
libdhcp_ddns_tuning_la_LIBADD += $(top_builddir)/src/lib/stats/libkea-stats.la
libdhcp_ddns_tuning_la_LIBADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
libdhcp_ddns_tuning_la_LIBADD += $(top_builddir)/src/lib/http/libkea-http.la
libdhcp_ddns_tuning_la_LIBADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
libdhcp_ddns_tuning_la_LIBADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
libdhcp_ddns_tuning_la_LIBADD += $(top_builddir)/src/lib/database/libkea-database.la
libdhcp_ddns_tuning_la_LIBADD += $(top_builddir)/src/lib/cc/libkea-cc.la
libdhcp_ddns_tuning_la_LIBADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libdhcp_ddns_tuning_la_LIBADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
libdhcp_ddns_tuning_la_LIBADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
libdhcp_ddns_tuning_la_LIBADD += $(top_builddir)/src/lib/log/libkea-log.la
libdhcp_ddns_tuning_la_LIBADD += $(top_builddir)/src/lib/util/libkea-util.la
libdhcp_ddns_tuning_la_LIBADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libdhcp_ddns_tuning_la_LIBADD += $(LOG4CPLUS_LIBS)
libdhcp_ddns_tuning_la_LIBADD += $(CRYPTO_LIBS)
libdhcp_ddns_tuning_la_LIBADD += $(BOOST_LIBS)

# If we want to get rid of all generated messages files, we need to use
# make maintainer-clean. The proper way to introduce custom commands for
# that operation is to define maintainer-clean-local target. However,
# make maintainer-clean also removes Makefile, so running configure script
# is required.  To make it easy to rebuild messages without going through
# reconfigure, a new target messages-clean has been added.
maintainer-clean-local:
	rm -f $(HOOK_NAME)_messages.h $(HOOK_NAME)_messages.cc

# To regenerate messages files, one can do:
#
# make messages-clean
# make messages
#
# This is needed only when a .mes file is modified.
messages-clean: maintainer-clean-local

if GENERATE_MESSAGES

# Define rule to build logging source files from message file
messages: $(HOOK_NAME)_messages.h $(HOOK_NAME)_messages.cc
	@echo Message files regenerated

$(HOOK_NAME)_messages.h $(HOOK_NAME)_messages.cc: $(HOOK_NAME)_messages.mes
	$(top_builddir)/src/lib/log/compiler/kea-msg-compiler $(top_srcdir)/src/hooks/dhcp/$(HOOK_NAME)/$(HOOK_NAME)_messages.mes

else

messages $(HOOK_NAME)_messages.h $(HOOK_NAME)_messages.cc:
	@echo Messages generation disabled. Configure with --enable-generate-messages to enable it.

endif
