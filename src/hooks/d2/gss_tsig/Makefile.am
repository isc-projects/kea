SUBDIRS = . testutils libloadtests tests

AM_CPPFLAGS  = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(GSSAPI_CFLAGS) $(BOOST_INCLUDES)
AM_CPPFLAGS += $(CRYPTO_CFLAGS) $(CRYPTO_INCLUDES)
AM_CXXFLAGS  = $(KEA_CXXFLAGS)

# Ensure that the message file is included in the distribution
EXTRA_DIST  = gss_tsig_messages.mes
EXTRA_DIST += gss_tsig.dox Doxyfile

CLEANFILES = *.gcno *.gcda

# convenience archive
noinst_LTLIBRARIES = libgss_tsig.la

libgss_tsig_la_SOURCES  = gss_tsig_callouts.cc
libgss_tsig_la_SOURCES += gss_tsig_cfg.cc gss_tsig_cfg.h
libgss_tsig_la_SOURCES += gss_tsig_context.cc gss_tsig_context.h
libgss_tsig_la_SOURCES += gss_tsig_impl.cc gss_tsig_impl.h
libgss_tsig_la_SOURCES += gss_tsig_key.cc gss_tsig_key.h
libgss_tsig_la_SOURCES += gss_tsig_log.cc gss_tsig_log.h
libgss_tsig_la_SOURCES += gss_tsig_messages.cc gss_tsig_messages.h
libgss_tsig_la_SOURCES += gss_tsig_api.cc gss_tsig_api.h
libgss_tsig_la_SOURCES += managed_key.cc managed_key.h
libgss_tsig_la_SOURCES += tkey_exchange.cc tkey_exchange.h
libgss_tsig_la_SOURCES += version.cc

libgss_tsig_la_CXXFLAGS = $(AM_CXXFLAGS)
libgss_tsig_la_CPPFLAGS = $(AM_CPPFLAGS)

# install the shared object into $(libdir)/kea/hooks
lib_hooksdir = $(libdir)/kea/hooks
lib_hooks_LTLIBRARIES = libddns_gss_tsig.la

libddns_gss_tsig_la_SOURCES =

libddns_gss_tsig_la_LDFLAGS  = $(AM_LDFLAGS)
libddns_gss_tsig_la_LDFLAGS  += -avoid-version -export-dynamic -module

libddns_gss_tsig_la_LIBADD  = libgss_tsig.la
libddns_gss_tsig_la_LIBADD += $(top_builddir)/src/lib/d2srv/libkea-d2srv.la
libddns_gss_tsig_la_LIBADD += $(top_builddir)/src/lib/asiodns/libkea-asiodns.la
libddns_gss_tsig_la_LIBADD += $(top_builddir)/src/lib/stats/libkea-stats.la
libddns_gss_tsig_la_LIBADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
libddns_gss_tsig_la_LIBADD += $(top_builddir)/src/lib/cc/libkea-cc.la
libddns_gss_tsig_la_LIBADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
libddns_gss_tsig_la_LIBADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
libddns_gss_tsig_la_LIBADD += $(top_builddir)/src/lib/log/libkea-log.la
libddns_gss_tsig_la_LIBADD += $(top_builddir)/src/lib/util/libkea-util.la
libddns_gss_tsig_la_LIBADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libddns_gss_tsig_la_LIBADD += $(GSSAPI_LIBS)
libddns_gss_tsig_la_LIBADD += $(LOG4CPLUS_LIBS)
libddns_gss_tsig_la_LIBADD += $(CRYPTO_LIBS)
libddns_gss_tsig_la_LIBADD += $(BOOST_LIBS)

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
	rm -f gss_tsig_messages.h gss_tsig_messages.cc

# To regenerate messages files, one can do:
#
# make messages-clean
# make messages
#
# This is needed only when a .mes file is modified.
messages-clean: maintainer-clean-local

if GENERATE_MESSAGES

# Define rule to build logging source files from message file
messages: gss_tsig_messages.h gss_tsig_messages.cc
	@echo Message files regenerated

gss_tsig_messages.h gss_tsig_messages.cc: gss_tsig_messages.mes
	(cd $(top_srcdir); \
	$(abs_top_builddir)/src/lib/log/compiler/kea-msg-compiler src/hooks/d2/gss_tsig/gss_tsig_messages.mes)

else

messages gss_tsig_messages.h gss_tsig_messages.cc:
	@echo Messages generation disabled. Configure with --enable-generate-messages to enable it.

endif
