SUBDIRS = . libloadtests tests

flex_id_dir = @localstatedir@/lib/@PACKAGE@

AM_CPPFLAGS  = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES) $(CRYPTO_CFLAGS) $(CRYPTO_INCLUDES)
AM_CPPFLAGS += -DFLEX_ID_DIR="\"$(flex_id_dir)\""
AM_CXXFLAGS  = $(KEA_CXXFLAGS)

EXTRA_DIST = libdhcp_flex_id.dox

# Ensure that the message file is included in the distribution
EXTRA_DIST += flex_id_messages.mes

CLEANFILES = *.gcno *.gcda

# convenience archive

noinst_LTLIBRARIES = libflexid.la

libflexid_la_SOURCES  =
libflexid_la_SOURCES += load_unload.cc
libflexid_la_SOURCES += callouts.cc
libflexid_la_SOURCES += flex_id.h
libflexid_la_SOURCES += flex_id_log.cc flex_id_log.h
libflexid_la_SOURCES += flex_id_messages.cc flex_id_messages.h
libflexid_la_SOURCES += version.cc

libflexid_la_CXXFLAGS = $(AM_CXXFLAGS)
libflexid_la_CPPFLAGS = $(AM_CPPFLAGS)

# install the shared object into $(libdir)/kea/hooks
lib_hooksdir = $(libdir)/kea/hooks
lib_hooks_LTLIBRARIES = libdhcp_flex_id.la

libdhcp_flex_id_la_SOURCES  =
libdhcp_flex_id_la_LDFLAGS  = $(AM_LDFLAGS)
libdhcp_flex_id_la_LDFLAGS  += -avoid-version -export-dynamic -module
libdhcp_flex_id_la_LIBADD  = libflexid.la
libdhcp_flex_id_la_LIBADD += $(top_builddir)/src/lib/process/libkea-process.la
libdhcp_flex_id_la_LIBADD += $(top_builddir)/src/lib/eval/libkea-eval.la
libdhcp_flex_id_la_LIBADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
libdhcp_flex_id_la_LIBADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
libdhcp_flex_id_la_LIBADD += $(top_builddir)/src/lib/cc/libkea-cc.la
libdhcp_flex_id_la_LIBADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libdhcp_flex_id_la_LIBADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
libdhcp_flex_id_la_LIBADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
libdhcp_flex_id_la_LIBADD += $(top_builddir)/src/lib/log/libkea-log.la
libdhcp_flex_id_la_LIBADD += $(top_builddir)/src/lib/util/libkea-util.la
libdhcp_flex_id_la_LIBADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libdhcp_flex_id_la_LIBADD += $(LOG4CPLUS_LIBS)
libdhcp_flex_id_la_LIBADD += $(CRYPTO_LIBS)
libdhcp_flex_id_la_LIBADD += $(BOOST_LIBS)

# Doxygen documentation

EXTRA_DIST += libdhcp_flex_id.dox Doxyfile

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
	rm -f flex_id_messages.h flex_id_messages.cc

# To regenerate messages files, one can do:
#
# make messages-clean
# make messages
#
# This is needed only when a .mes file is modified.
messages-clean: maintainer-clean-local

if GENERATE_MESSAGES

# Define rule to build logging source files from message file
messages: flex_id_messages.h flex_id_messages.cc
	@echo Message files regenerated

flex_id_messages.h flex_id_messages.cc: flex_id_messages.mes
	(cd $(top_srcdir); \
	$(abs_top_builddir)/src/lib/log/compiler/kea-msg-compiler src/hooks/dhcp/flex_id/flex_id_messages.mes)

else

messages flex_id_messages.h flex_id_messages.cc:
	@echo Messages generation disabled. Configure with --enable-generate-messages to enable it.

endif
