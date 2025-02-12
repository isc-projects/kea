SUBDIRS = . libloadtests tests

AM_CPPFLAGS  = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES) $(CRYPTO_CFLAGS) $(CRYPTO_INCLUDES)
AM_CXXFLAGS  = $(KEA_CXXFLAGS)

# Ensure that the message file and doxygen file is included in the distribution
EXTRA_DIST = ping_check_messages.mes

CLEANFILES = *.gcno *.gcda

# convenience archive

noinst_LTLIBRARIES = libping_check.la

libping_check_la_SOURCES = ping_check_callouts.cc
libping_check_la_SOURCES += ping_check_log.cc ping_check_log.h
libping_check_la_SOURCES += ping_check_messages.cc ping_check_messages.h
libping_check_la_SOURCES += icmp_endpoint.h icmp_socket.h
libping_check_la_SOURCES += ping_context.cc ping_context.h
libping_check_la_SOURCES += ping_context_store.cc ping_context_store.h
libping_check_la_SOURCES += icmp_msg.h icmp_msg.cc
libping_check_la_SOURCES += ping_channel.cc ping_channel.h
libping_check_la_SOURCES += ping_check_mgr.cc ping_check_mgr.h
libping_check_la_SOURCES += ping_check_config.cc ping_check_config.h
libping_check_la_SOURCES += config_cache.cc config_cache.h
libping_check_la_SOURCES += version.cc

libping_check_la_CXXFLAGS = $(AM_CXXFLAGS)
libping_check_la_CPPFLAGS = $(AM_CPPFLAGS)

# install the shared object into $(libdir)/kea/hooks
lib_hooksdir = $(libdir)/kea/hooks
lib_hooks_LTLIBRARIES = libdhcp_ping_check.la

libdhcp_ping_check_la_SOURCES  =
libdhcp_ping_check_la_LDFLAGS  = $(AM_LDFLAGS)
libdhcp_ping_check_la_LDFLAGS  += -avoid-version -export-dynamic -module
libdhcp_ping_check_la_LIBADD  = libping_check.la
libdhcp_ping_check_la_LIBADD += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
libdhcp_ping_check_la_LIBADD += $(top_builddir)/src/lib/process/libkea-process.la
libdhcp_ping_check_la_LIBADD += $(top_builddir)/src/lib/eval/libkea-eval.la
libdhcp_ping_check_la_LIBADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
libdhcp_ping_check_la_LIBADD += $(top_builddir)/src/lib/stats/libkea-stats.la
libdhcp_ping_check_la_LIBADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
libdhcp_ping_check_la_LIBADD += $(top_builddir)/src/lib/http/libkea-http.la
libdhcp_ping_check_la_LIBADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
libdhcp_ping_check_la_LIBADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
libdhcp_ping_check_la_LIBADD += $(top_builddir)/src/lib/database/libkea-database.la
libdhcp_ping_check_la_LIBADD += $(top_builddir)/src/lib/cc/libkea-cc.la
libdhcp_ping_check_la_LIBADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libdhcp_ping_check_la_LIBADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
libdhcp_ping_check_la_LIBADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
libdhcp_ping_check_la_LIBADD += $(top_builddir)/src/lib/log/libkea-log.la
libdhcp_ping_check_la_LIBADD += $(top_builddir)/src/lib/util/libkea-util.la
libdhcp_ping_check_la_LIBADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libdhcp_ping_check_la_LIBADD += $(LOG4CPLUS_LIBS)
libdhcp_ping_check_la_LIBADD += $(CRYPTO_LIBS)
libdhcp_ping_check_la_LIBADD += $(BOOST_LIBS)

# Doxygen documentation
EXTRA_DIST += ping_check.dox Doxyfile Doxyfile-xml

devel:
	mkdir -p html
	(cat Doxyfile; echo PROJECT_NUMBER=$(PACKAGE_VERSION)) | doxygen - > html/doxygen.log 2> html/doxygen-error.log
	echo `grep -i ": warning:" html/doxygen-error.log | wc -l` warnings/errors detected.

clean-local:
	rm -rf html

# If we want to get rid of all generated messages files, we need to use
# make maintainer-clean. The proper way to introduce custom commands for
# that operation is to define maintainer-clean-local target. However,
# make maintainer-clean also removes Makefile, so running configure script
# is required.  To make it easy to rebuild messages without going through
# reconfigure, a new target messages-clean has been added.
maintainer-clean-local:
	rm -f ping_check_messages.h ping_check_messages.cc

# To regenerate messages files, one can do:
#
# make messages-clean
# make messages
#
# This is needed only when a .mes file is modified.
messages-clean: maintainer-clean-local

if GENERATE_MESSAGES

# Define rule to build logging source files from message file
messages: ping_check_messages.h ping_check_messages.cc
	@echo Message files regenerated

ping_check_messages.h ping_check_messages.cc: ping_check_messages.mes
	$(top_builddir)/src/lib/log/compiler/kea-msg-compiler $(top_srcdir)/src/hooks/dhcp/ping_check/ping_check_messages.mes

else

messages ping_check_messages.h ping_check_messages.cc:
	@echo Messages generation disabled. Configure with --enable-generate-messages to enable it.

endif
