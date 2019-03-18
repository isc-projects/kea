SUBDIRS = . tests

AM_CPPFLAGS  = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS  = $(KEA_CXXFLAGS)

# Ensure that the message file is included in the distribution
EXTRA_DIST = dhcp_ddns_messages.mes libdhcp_ddns.dox

CLEANFILES = *.gcno *.gcda

lib_LTLIBRARIES = libkea-dhcp_ddns.la
libkea_dhcp_ddns_la_SOURCES  =
libkea_dhcp_ddns_la_SOURCES += dhcp_ddns_log.cc dhcp_ddns_log.h
libkea_dhcp_ddns_la_SOURCES += dhcp_ddns_messages.cc dhcp_ddns_messages.h
libkea_dhcp_ddns_la_SOURCES += ncr_io.cc ncr_io.h
libkea_dhcp_ddns_la_SOURCES += ncr_msg.cc ncr_msg.h
libkea_dhcp_ddns_la_SOURCES += ncr_udp.cc ncr_udp.h

libkea_dhcp_ddns_la_CXXFLAGS = $(AM_CXXFLAGS)
libkea_dhcp_ddns_la_CPPFLAGS = $(AM_CPPFLAGS)
libkea_dhcp_ddns_la_LDFLAGS  = $(AM_LDFLAGS)
libkea_dhcp_ddns_la_LDFLAGS += $(CRYPTO_LDFLAGS)
libkea_dhcp_ddns_la_LDFLAGS += -no-undefined -version-info 1:3:0

libkea_dhcp_ddns_la_LIBADD  =
libkea_dhcp_ddns_la_LIBADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
libkea_dhcp_ddns_la_LIBADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
libkea_dhcp_ddns_la_LIBADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libkea_dhcp_ddns_la_LIBADD += $(top_builddir)/src/lib/cc/libkea-cc.la
libkea_dhcp_ddns_la_LIBADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
libkea_dhcp_ddns_la_LIBADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
libkea_dhcp_ddns_la_LIBADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
libkea_dhcp_ddns_la_LIBADD += $(top_builddir)/src/lib/log/libkea-log.la
libkea_dhcp_ddns_la_LIBADD += $(top_builddir)/src/lib/util/threads/libkea-threads.la
libkea_dhcp_ddns_la_LIBADD += $(top_builddir)/src/lib/util/libkea-util.la
libkea_dhcp_ddns_la_LIBADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libkea_dhcp_ddns_la_LIBADD += $(LOG4CPLUS_LIBS) $(CRYPTO_LIBS) $(BOOST_LIBS)

# If we want to get rid of all generated messages files, we need to use
# make maintainer-clean. The proper way to introduce custom commands for
# that operation is to define maintainer-clean-local target. However,
# make maintainer-clean also removes Makefile, so running configure script
# is required.  To make it easy to rebuild messages without going through
# reconfigure, a new target messages-clean has been added.
maintainer-clean-local:
	rm -f dhcp_ddns_messages.h dhcp_ddns_messages.cc

# To regenerate messages files, one can do:
#
# make messages-clean
# make messages
#
# This is needed only when a .mes file is modified.
messages-clean: maintainer-clean-local

if GENERATE_MESSAGES

# Define rule to build logging source files from message file
messages: dhcp_ddns_messages.h dhcp_ddns_messages.cc
	@echo Message files regenerated

dhcp_ddns_messages.h dhcp_ddns_messages.cc: dhcp_ddns_messages.mes
	$(top_builddir)/src/lib/log/compiler/kea-msg-compiler $(top_srcdir)/src/lib/dhcp_ddns/dhcp_ddns_messages.mes

else

messages dhcp_ddns_messages.h dhcp_ddns_messages.cc:
	@echo Messages generation disabled. Configure with --enable-generate-messages to enable it.

endif

# Specify the headers for copying into the installation directory tree.
libkea_dhcp_ddns_includedir = $(pkgincludedir)/dhcp_ddns
libkea_dhcp_ddns_include_HEADERS = \
	dhcp_ddns_log.h \
	dhcp_ddns_messages.h \
	ncr_io.h \
	ncr_msg.h \
	ncr_udp.h
