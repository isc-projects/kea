SUBDIRS = . tests

AM_CPPFLAGS  = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS  = $(KEA_CXXFLAGS)

EXTRA_DIST = libdhcp_scripts.dox
# Ensure that the message file is included in the distribution
EXTRA_DIST += scripts_messages.mes

CLEANFILES = *.gcno *.gcda

# convenience archive

noinst_LTLIBRARIES = libscripts.la

libscripts_la_SOURCES  =
libscripts_la_SOURCES += load_unload.cc
libscripts_la_SOURCES += pkt_send_co.cc
libscripts_la_SOURCES += lease_expire_co.cc
libscripts_la_SOURCES += scripts_cfg.cc scripts_cfg.h
libscripts_la_SOURCES += scripts_log.cc scripts_log.h
libscripts_la_SOURCES += scripts_messages.cc scripts_messages.h
libscripts_la_SOURCES += version.cc

libscripts_la_CXXFLAGS = $(AM_CXXFLAGS)
libscripts_la_CPPFLAGS = $(AM_CPPFLAGS)

noinst_LTLIBRARIES += libdhcp_scripts.la

libdhcp_scripts_la_SOURCES  =
libdhcp_scripts_la_LDFLAGS  = $(AM_LDFLAGS)
libdhcp_scripts_la_LDFLAGS  += -avoid-version -export-dynamic -module
# -rpath /nowhere is a hack to trigger libtool to not create a
# convenience archive, resulting in shared modules
libdhcp_scripts_la_LDFLAGS  += -rpath /nowhere
libdhcp_scripts_la_LIBADD  = libscripts.la
libdhcp_scripts_la_LIBADD  += $(top_builddir)/src/lib/hooks/libkea-hooks.la
libdhcp_scripts_la_LIBADD  += $(top_builddir)/src/lib/log/libkea-log.la
libdhcp_scripts_la_LIBADD  += $(top_builddir)/src/lib/util/threads/libkea-threads.la
libdhcp_scripts_la_LIBADD  += $(top_builddir)/src/lib/util/libkea-util.la
libdhcp_scripts_la_LIBADD  += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libdhcp_scripts_la_LIBADD  += $(LOG4CPLUS_LIBS)

# If we want to get rid of all generated messages files, we need to use
# make maintainer-clean. The proper way to introduce custom commands for
# that operation is to define maintainer-clean-local target. However,
# make maintainer-clean also removes Makefile, so running configure script
# is required.  To make it easy to rebuild messages without going through
# reconfigure, a new target messages-clean has been added.
maintainer-clean-local:
	rm -f scripts_messages.h scripts_messages.cc

# To regenerate messages files, one can do:
#
# make messages-clean
# make messages
#
# This is needed only when a .mes file is modified.
messages-clean: maintainer-clean-local

if GENERATE_MESSAGES

# Define rule to build logging source files from message file
messages: scripts_messages.h scripts_messages.cc
	@echo Message files regenerated

scripts_messages.h scripts_messages.cc: scripts_messages.mes
	$(top_builddir)/src/lib/log/compiler/kea-msg-compiler $(top_srcdir)/src/hooks/dhcp/scripts/scripts_messages.mes

else

messages scripts_messages.h scripts_messages.cc:
	@echo Messages generation disabled. Configure with --enable-generate-messages to enable it.

endif

