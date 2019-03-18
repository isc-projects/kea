SUBDIRS = . tests

AM_CPPFLAGS  = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS  = $(KEA_CXXFLAGS)

# Ensure that the message file and doxygen file is included in the distribution
EXTRA_DIST = lease_cmds_messages.mes
EXTRA_DIST += lease_cmds.dox

CLEANFILES = *.gcno *.gcda

# convenience archive

noinst_LTLIBRARIES = liblease_cmds.la

liblease_cmds_la_SOURCES  = lease_cmds.cc lease_cmds.h
liblease_cmds_la_SOURCES += lease_cmds_callouts.cc
liblease_cmds_la_SOURCES += lease_parser.h lease_parser.cc
liblease_cmds_la_SOURCES += lease_cmds_log.cc lease_cmds_log.h
liblease_cmds_la_SOURCES += lease_cmds_messages.cc lease_cmds_messages.h
liblease_cmds_la_SOURCES += version.cc

liblease_cmds_la_CXXFLAGS = $(AM_CXXFLAGS)
liblease_cmds_la_CPPFLAGS = $(AM_CPPFLAGS)

# install the shared object into $(libdir)/kea/hooks
lib_hooksdir = $(libdir)/kea/hooks
lib_hooks_LTLIBRARIES = libdhcp_lease_cmds.la

libdhcp_lease_cmds_la_SOURCES  =
libdhcp_lease_cmds_la_LDFLAGS  = $(AM_LDFLAGS)
libdhcp_lease_cmds_la_LDFLAGS  += -avoid-version -export-dynamic -module
libdhcp_lease_cmds_la_LIBADD  = liblease_cmds.la
libdhcp_lease_cmds_la_LIBADD  += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
libdhcp_lease_cmds_la_LIBADD  += $(top_builddir)/src/lib/process/libkea-process.la
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

# If we want to get rid of all generated messages files, we need to use
# make maintainer-clean. The proper way to introduce custom commands for
# that operation is to define maintainer-clean-local target. However,
# make maintainer-clean also removes Makefile, so running configure script
# is required.  To make it easy to rebuild messages without going through
# reconfigure, a new target messages-clean has been added.
maintainer-clean-local:
	rm -f lease_cmds_messages.h lease_cmds_messages.cc

# To regenerate messages files, one can do:
#
# make messages-clean
# make messages
#
# This is needed only when a .mes file is modified.
messages-clean: maintainer-clean-local

if GENERATE_MESSAGES

# Define rule to build logging source files from message file
messages: lease_cmds_messages.h lease_cmds_messages.cc
	@echo Message files regenerated

lease_cmds_messages.h lease_cmds_messages.cc: lease_cmds_messages.mes
	$(top_builddir)/src/lib/log/compiler/kea-msg-compiler $(top_srcdir)/src/hooks/dhcp/lease_cmds/lease_cmds_messages.mes

else

messages lease_cmds_messages.h lease_cmds_messages.cc:
	@echo Messages generation disabled. Configure with --enable-generate-messages to enable it.

endif

