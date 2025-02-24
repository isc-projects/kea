SUBDIRS = . libloadtests tests

legal_log_dir = @localstatedir@/lib/@PACKAGE@

AM_CPPFLAGS  = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES) $(CRYPTO_CFLAGS) $(CRYPTO_INCLUDES)
AM_CPPFLAGS += -DLEGAL_LOG_DIR="\"$(legal_log_dir)\""

AM_CXXFLAGS  = $(KEA_CXXFLAGS)

# Some versions of GCC warn about some versions of Boost regarding
# missing initializer for members in its posix_time.
# https://svn.boost.org/trac/boost/ticket/3477
# But older GCC compilers don't have the flag.
AM_CXXFLAGS += $(WARNING_NO_MISSING_FIELD_INITIALIZERS_CFLAG)

EXTRA_DIST =

# Ensure that the message file is included in the distribution
EXTRA_DIST += legal_log_messages.mes

CLEANFILES = *.gcno *.gcda

# convenience archive

noinst_LTLIBRARIES = liblegl.la

liblegl_la_SOURCES  =
liblegl_la_SOURCES += load_unload.cc
liblegl_la_SOURCES += command_callouts.cc
liblegl_la_SOURCES += lease4_callouts.cc
liblegl_la_SOURCES += lease6_callouts.cc
liblegl_la_SOURCES += legal_log_log.cc legal_log_log.h
liblegl_la_SOURCES += legal_log_messages.cc legal_log_messages.h
liblegl_la_SOURCES += rotating_file.cc rotating_file.h
liblegl_la_SOURCES += subnets_user_context.h
liblegl_la_SOURCES += version.cc

liblegl_la_CXXFLAGS = $(AM_CXXFLAGS)
liblegl_la_CPPFLAGS = $(AM_CPPFLAGS)

# install the shared object into $(libdir)/kea/hooks
lib_hooksdir = $(libdir)/kea/hooks
lib_hooks_LTLIBRARIES = libdhcp_legal_log.la

libdhcp_legal_log_la_SOURCES  =
libdhcp_legal_log_la_LDFLAGS  = $(AM_LDFLAGS)
libdhcp_legal_log_la_LDFLAGS  += -avoid-version -export-dynamic -module
libdhcp_legal_log_la_LIBADD  = liblegl.la
libdhcp_legal_log_la_LIBADD += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
libdhcp_legal_log_la_LIBADD += $(top_builddir)/src/lib/process/libkea-process.la
libdhcp_legal_log_la_LIBADD += $(top_builddir)/src/lib/eval/libkea-eval.la
libdhcp_legal_log_la_LIBADD += $(top_builddir)/src/lib/stats/libkea-stats.la
libdhcp_legal_log_la_LIBADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
libdhcp_legal_log_la_LIBADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
libdhcp_legal_log_la_LIBADD += $(top_builddir)/src/lib/database/libkea-database.la
libdhcp_legal_log_la_LIBADD += $(top_builddir)/src/lib/cc/libkea-cc.la
libdhcp_legal_log_la_LIBADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libdhcp_legal_log_la_LIBADD += $(top_builddir)/src/lib/log/libkea-log.la
libdhcp_legal_log_la_LIBADD += $(top_builddir)/src/lib/util/libkea-util.la
libdhcp_legal_log_la_LIBADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libdhcp_legal_log_la_LIBADD += $(LOG4CPLUS_LIBS)
libdhcp_legal_log_la_LIBADD += $(BOOST_LIBS)
libdhcp_legal_log_la_LIBADD += $(CRYPTO_LIBS)

# Doxygen documentation

EXTRA_DIST += libdhcp_legal_log.dox Doxyfile

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
	rm -f legal_log_messages.h legal_log_messages.cc

# To regenerate messages files, one can do:
#
# make messages-clean
# make messages
#
# This is needed only when a .mes file is modified.
messages-clean: maintainer-clean-local

if GENERATE_MESSAGES

# Define rule to build logging source files from message file
messages: legal_log_messages.h legal_log_messages.cc
	@echo Message files regenerated

legal_log_messages.h legal_log_messages.cc: legal_log_messages.mes
	(cd $(top_srcdir); \
	$(abs_top_builddir)/src/lib/log/compiler/kea-msg-compiler src/hooks/dhcp/forensic_log/legal_log_messages.mes)

else

messages legal_log_messages.h legal_log_messages.cc:
	@echo Messages generation disabled. Configure with --enable-generate-messages to enable it.

endif
