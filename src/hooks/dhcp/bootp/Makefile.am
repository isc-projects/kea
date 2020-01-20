SUBDIRS = . tests

AM_CPPFLAGS  = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS  = $(KEA_CXXFLAGS)

# Ensure that the message file and doxygen file is included in the distribution
EXTRA_DIST = bootp_messages.mes
EXTRA_DIST += bootp.dox

CLEANFILES = *.gcno *.gcda

# convenience archive

noinst_LTLIBRARIES = libbootp.la

libbootp_la_SOURCES  = bootp_callouts.cc
libbootp_la_SOURCES += bootp_log.cc bootp_log.h
libbootp_la_SOURCES += bootp_messages.cc bootp_messages.h
libbootp_la_SOURCES += version.cc

libbootp_la_CXXFLAGS = $(AM_CXXFLAGS)
libbootp_la_CPPFLAGS = $(AM_CPPFLAGS)

# install the shared object into $(libdir)/kea/hooks
lib_hooksdir = $(libdir)/kea/hooks
lib_hooks_LTLIBRARIES = libdhcp_bootp.la

libdhcp_bootp_la_SOURCES  =
libdhcp_bootp_la_LDFLAGS  = $(AM_LDFLAGS)
libdhcp_bootp_la_LDFLAGS  += -avoid-version -export-dynamic -module
libdhcp_bootp_la_LIBADD = libbootp.la
libdhcp_bootp_la_LIBADD += $(top_builddir)/src/lib/stats/libkea-stats.la
libdhcp_bootp_la_LIBADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
libdhcp_bootp_la_LIBADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
libdhcp_bootp_la_LIBADD += $(top_builddir)/src/lib/database/libkea-database.la
libdhcp_bootp_la_LIBADD += $(top_builddir)/src/lib/cc/libkea-cc.la
libdhcp_bootp_la_LIBADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libdhcp_bootp_la_LIBADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
libdhcp_bootp_la_LIBADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
libdhcp_bootp_la_LIBADD += $(top_builddir)/src/lib/log/libkea-log.la
libdhcp_bootp_la_LIBADD += $(top_builddir)/src/lib/util/libkea-util.la
libdhcp_bootp_la_LIBADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libdhcp_bootp_la_LIBADD += $(LOG4CPLUS_LIBS)
libdhcp_bootp_la_LIBADD += $(CRYPTO_LIBS)
libdhcp_bootp_la_LIBADD += $(BOOST_LIBS)

# If we want to get rid of all generated messages files, we need to use
# make maintainer-clean. The proper way to introduce custom commands for
# that operation is to define maintainer-clean-local target. However,
# make maintainer-clean also removes Makefile, so running configure script
# is required.  To make it easy to rebuild messages without going through
# reconfigure, a new target messages-clean has been added.
maintainer-clean-local:
	rm -f bootp_messages.h bootp_messages.cc

# To regenerate messages files, one can do:
#
# make messages-clean
# make messages
#
# This is needed only when a .mes file is modified.
messages-clean: maintainer-clean-local

if GENERATE_MESSAGES

# Define rule to build logging source files from message file
messages: bootp_messages.h bootp_messages.cc
	@echo Message files regenerated

bootp_messages.h bootp_messages.cc: bootp_messages.mes
	$(top_builddir)/src/lib/log/compiler/kea-msg-compiler $(top_srcdir)/src/hooks/dhcp/bootp/bootp_messages.mes

else

messages bootp_messages.h bootp_messages.cc:
	@echo Messages generation disabled. Configure with --enable-generate-messages to enable it.

endif

