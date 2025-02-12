SUBDIRS = . libloadtests tests

AM_CPPFLAGS  = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES) $(CRYPTO_CFLAGS) $(CRYPTO_INCLUDES)
AM_CXXFLAGS  = $(KEA_CXXFLAGS)

# Ensure that the message file is included in the distribution
EXTRA_DIST = host_cmds_messages.mes

CLEANFILES = *.gcno *.gcda

# convenience archive

noinst_LTLIBRARIES = libhost_cmds.la

libhost_cmds_la_SOURCES  = host_cmds.cc host_cmds.h
libhost_cmds_la_SOURCES += host_cmds_callouts.cc
libhost_cmds_la_SOURCES += host_data_parser.h
libhost_cmds_la_SOURCES += host_cmds_log.cc host_cmds_log.h
libhost_cmds_la_SOURCES += host_cmds_messages.cc host_cmds_messages.h
libhost_cmds_la_SOURCES += version.cc

libhost_cmds_la_CXXFLAGS = $(AM_CXXFLAGS)
libhost_cmds_la_CPPFLAGS = $(AM_CPPFLAGS)

# install the shared object into $(libdir)/kea/hooks
lib_hooksdir = $(libdir)/kea/hooks
lib_hooks_LTLIBRARIES = libdhcp_host_cmds.la

libdhcp_host_cmds_la_SOURCES  =
libdhcp_host_cmds_la_LDFLAGS  = $(AM_LDFLAGS)
libdhcp_host_cmds_la_LDFLAGS  += -avoid-version -export-dynamic -module
libdhcp_host_cmds_la_LIBADD  = libhost_cmds.la
libdhcp_host_cmds_la_LIBADD += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
libdhcp_host_cmds_la_LIBADD += $(top_builddir)/src/lib/process/libkea-process.la
libdhcp_host_cmds_la_LIBADD += $(top_builddir)/src/lib/eval/libkea-eval.la
libdhcp_host_cmds_la_LIBADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
libdhcp_host_cmds_la_LIBADD += $(top_builddir)/src/lib/stats/libkea-stats.la
libdhcp_host_cmds_la_LIBADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
libdhcp_host_cmds_la_LIBADD += $(top_builddir)/src/lib/http/libkea-http.la
libdhcp_host_cmds_la_LIBADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
libdhcp_host_cmds_la_LIBADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
libdhcp_host_cmds_la_LIBADD += $(top_builddir)/src/lib/cc/libkea-cc.la
libdhcp_host_cmds_la_LIBADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libdhcp_host_cmds_la_LIBADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
libdhcp_host_cmds_la_LIBADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
libdhcp_host_cmds_la_LIBADD += $(top_builddir)/src/lib/log/libkea-log.la
libdhcp_host_cmds_la_LIBADD += $(top_builddir)/src/lib/util/libkea-util.la
libdhcp_host_cmds_la_LIBADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la

EXTRA_DIST += host_cmds.dox Doxyfile Doxyfile-xml

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
# is required. To make it easy to rebuild messages without going through
# reconfigure, a new target messages-clean has been added.
maintainer-clean-local:
	rm -f host_cmds_messages.h host_cmds_messages.cc

# To regenerate messages files, one can do:
#
# make messages-clean
# make messages
#
# This is needed only when a .mes file is modified.
messages-clean: maintainer-clean-local

if GENERATE_MESSAGES

# Define rule to build logging source files from message file
messages: host_cmds_messages.h host_cmds_messages.cc
	@echo Message files regenerated

host_cmds_messages.h host_cmds_messages.cc: host_cmds_messages.mes
	$(top_builddir)/src/lib/log/compiler/kea-msg-compiler $(top_srcdir)/src/hooks/dhcp/host_cmds/host_cmds_messages.mes

else

messages host_cmds_messages.h host_cmds_messages.cc:
	@echo Messages generation disabled. Configure with --enable-generate-messages to enable it.

endif
