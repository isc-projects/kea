SUBDIRS = . libloadtests tests

limits_dir = @localstatedir@/lib/@PACKAGE@

AM_CPPFLAGS  =
AM_CPPFLAGS += -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/hooks/dhcp -I$(top_srcdir)/src/hooks/dhcp
AM_CPPFLAGS += $(BOOST_INCLUDES) $(CRYPTO_CFLAGS) $(CRYPTO_INCLUDES)
AM_CXXFLAGS = $(KEA_CXXFLAGS)


if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

EXTRA_DIST =

# Ensure that the message file is included in the distribution.
EXTRA_DIST += limits_messages.mes

CLEANFILES = *.gcno *.gcda

# Internal library

noinst_LTLIBRARIES = liblimits.la

liblimits_la_SOURCES  =
liblimits_la_SOURCES += configuration.cc configuration.h
liblimits_la_SOURCES += dhcpv4_callouts.cc
liblimits_la_SOURCES += dhcpv6_callouts.cc
liblimits_la_SOURCES += limits_logger.cc limits_logger.h
liblimits_la_SOURCES += limits_messages.cc limits_messages.h
liblimits_la_SOURCES += load_unload.cc
liblimits_la_SOURCES += limit_manager.cc limit_manager.h
liblimits_la_SOURCES += version.cc

liblimits_la_CXXFLAGS = $(AM_CXXFLAGS)
liblimits_la_CPPFLAGS = $(AM_CPPFLAGS)

# install the shared object into $(libdir)/kea/hooks
lib_hooksdir = $(libdir)/kea/hooks
lib_hooks_LTLIBRARIES = libdhcp_limits.la

libdhcp_limits_la_SOURCES  =
libdhcp_limits_la_LDFLAGS  = $(AM_LDFLAGS)
libdhcp_limits_la_LDFLAGS += -avoid-version -export-dynamic -module
libdhcp_limits_la_LIBADD  = liblimits.la
libdhcp_limits_la_LIBADD += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
libdhcp_limits_la_LIBADD += $(top_builddir)/src/lib/process/libkea-process.la
libdhcp_limits_la_LIBADD += $(top_builddir)/src/lib/eval/libkea-eval.la
libdhcp_limits_la_LIBADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
libdhcp_limits_la_LIBADD += $(top_builddir)/src/lib/stats/libkea-stats.la
libdhcp_limits_la_LIBADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
libdhcp_limits_la_LIBADD += $(top_builddir)/src/lib/http/libkea-http.la
libdhcp_limits_la_LIBADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
libdhcp_limits_la_LIBADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
libdhcp_limits_la_LIBADD += $(top_builddir)/src/lib/database/libkea-database.la
libdhcp_limits_la_LIBADD += $(top_builddir)/src/lib/cc/libkea-cc.la
libdhcp_limits_la_LIBADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libdhcp_limits_la_LIBADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
libdhcp_limits_la_LIBADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
libdhcp_limits_la_LIBADD += $(top_builddir)/src/lib/log/libkea-log.la
libdhcp_limits_la_LIBADD += $(top_builddir)/src/lib/util/libkea-util.la
libdhcp_limits_la_LIBADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libdhcp_limits_la_LIBADD += $(LOG4CPLUS_LIBS)

# Doxygen documentation

EXTRA_DIST += libdhcp_limits.dox Doxyfile

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
	rm -f limits_messages.cc limits_messages.h

# To regenerate messages files, one can do:
#
# make messages-clean
# make messages
#
# This is needed only when a .mes file is modified.
messages-clean: maintainer-clean-local

if GENERATE_MESSAGES

# Define rule to build logging source files from message file
messages: limits_messages.h limits_messages.cc
	@echo Message files regenerated

limits_messages.h limits_messages.cc: limits_messages.mes
	(cd $(top_srcdir); \
	$(abs_top_builddir)/src/lib/log/compiler/kea-msg-compiler src/hooks/dhcp/limits/limits_messages.mes)

else

messages limits_messages.h limits_messages.cc:
	@echo Messages generation disabled. Configure with --enable-generate-messages to enable it.

endif
