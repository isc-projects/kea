SUBDIRS = . libloadtests tests

dictionarydir = @sysconfdir@/@PACKAGE@/radius

AM_CPPFLAGS  = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES) $(CRYPTO_CFLAGS) $(CRYPTO_INCLUDES)
DICTIONARY = $(sysconfdir)/@PACKAGE@/radius/dictionary
AM_CPPFLAGS += -DDICTIONARY=\"$(DICTIONARY)\"
AM_CXXFLAGS  = $(KEA_CXXFLAGS)

# Ensure that the message file is included in the distribution
EXTRA_DIST = radius_messages.mes

CLEANFILES = *.gcno *.gcda

# dictionary
dictionary_DATA = data/dictionary

EXTRA_DIST += $(dictionary_DATA)

# convenience archive

noinst_LTLIBRARIES = libradius.la

libradius_la_SOURCES  =
libradius_la_SOURCES += cfg_attribute.cc cfg_attribute.h
libradius_la_SOURCES += client.h
libradius_la_SOURCES += client_attribute.cc client_attribute.h
libradius_la_SOURCES += client_dictionary.cc client_dictionary.h
libradius_la_SOURCES += client_exchange.cc client_exchange.h
libradius_la_SOURCES += client_message.cc client_message.h
libradius_la_SOURCES += client_server.cc client_server.h
libradius_la_SOURCES += radius.cc radius.h
libradius_la_SOURCES += radius_access.cc radius_access.h
libradius_la_SOURCES += radius_accounting.cc radius_accounting.h
libradius_la_SOURCES += radius_backend.cc radius_backend.h
libradius_la_SOURCES += radius_callout.cc
libradius_la_SOURCES += radius_log.cc radius_log.h
libradius_la_SOURCES += radius_messages.cc radius_messages.h
libradius_la_SOURCES += radius_parsers.cc radius_parsers.h
libradius_la_SOURCES += radius_request.cc radius_request.h
libradius_la_SOURCES += radius_service.cc radius_service.h
libradius_la_SOURCES += radius_utils.cc radius_utils.h
libradius_la_SOURCES += version.cc

libradius_la_CXXFLAGS = $(AM_CXXFLAGS)
libradius_la_CPPFLAGS = $(AM_CPPFLAGS)

# install the shared object into $(libdir)/kea/hooks
lib_hooksdir = $(libdir)/kea/hooks
lib_hooks_LTLIBRARIES = libdhcp_radius.la

libdhcp_radius_la_SOURCES  =
libdhcp_radius_la_LDFLAGS  = $(AM_LDFLAGS)
libdhcp_radius_la_LDFLAGS  += -avoid-version -export-dynamic -module
libdhcp_radius_la_LIBADD  = libradius.la
libdhcp_radius_la_LIBADD += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
libdhcp_radius_la_LIBADD += $(top_builddir)/src/lib/process/libkea-process.la
libdhcp_radius_la_LIBADD += $(top_builddir)/src/lib/eval/libkea-eval.la
libdhcp_radius_la_LIBADD += $(top_builddir)/src/lib/stats/libkea-stats.la
libdhcp_radius_la_LIBADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
libdhcp_radius_la_LIBADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
libdhcp_radius_la_LIBADD += $(top_builddir)/src/lib/cc/libkea-cc.la
libdhcp_radius_la_LIBADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libdhcp_radius_la_LIBADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
libdhcp_radius_la_LIBADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
libdhcp_radius_la_LIBADD += $(top_builddir)/src/lib/log/libkea-log.la
libdhcp_radius_la_LIBADD += $(top_builddir)/src/lib/util/libkea-util.la
libdhcp_radius_la_LIBADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libdhcp_radius_la_LIBADD += $(LOG4CPLUS_LIBS)
libdhcp_radius_la_LIBADD += $(BOOST_LIBS)

# Doxygen documentation

EXTRA_DIST += radius.dox Doxyfile

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
	rm -f radius_messages.h radius_messages.cc

# To regenerate messages files, one can do:
#
# make messages-clean
# make messages
#
# This is needed only when a .mes file is modified.
messages-clean: maintainer-clean-local

if GENERATE_MESSAGES

# Define rule to build logging source files from message file
messages: radius_messages.h radius_messages.cc
	@echo Message files regenerated

radius_messages.h radius_messages.cc: radius_messages.mes
	(cd $(top_srcdir); \
	$(abs_top_builddir)/src/lib/log/compiler/kea-msg-compiler src/hooks/dhcp/radius/radius_messages.mes)

else

messages radius_messages.h radius_messages.cc:
	@echo Messages generation disabled. Configure with --enable-generate-messages to enable it.

endif
