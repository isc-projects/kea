SUBDIRS = . tests libloadtests

legal_log_dir = @localstatedir@/@PACKAGE@/var

AM_CPPFLAGS  = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS +=  -DLEGAL_LOG_DIR="\"$(legal_log_dir)\""
AM_CXXFLAGS  = $(KEA_CXXFLAGS)

# Some versions of GCC warn about some versions of Boost regarding
# missing initializer for members in its posix_time.
# https://svn.boost.org/trac/boost/ticket/3477
# But older GCC compilers don't have the flag.
AM_CXXFLAGS += $(WARNING_NO_MISSING_FIELD_INITIALIZERS_CFLAG)

# Define rule to build logging source files from message file
legal_log_messages.h legal_log_messages.cc: s-messages
s-messages: legal_log_messages.mes
	$(top_builddir)/src/lib/log/compiler/kea-msg-compiler $(top_srcdir)/src/hooks/dhcp/legal_log/legal_log_messages.mes
	touch $@

# Tell automake that the message files are built as part of the build process
# (so that they are built before the main library is built).
BUILT_SOURCES = legal_log_messages.h legal_log_messages.cc

EXTRA_DIST = libdhcp_legal_log.dox
# Ensure that the message file is included in the distribution
EXTRA_DIST += legal_log_messages.mes

# Get rid of generated message files on a clean
CLEANFILES = *.gcno *.gcda legal_log_messages.h legal_log_messages.cc s-messages

# convenience archive

noinst_LTLIBRARIES = liblegl.la

liblegl_la_SOURCES  =
liblegl_la_SOURCES += load_unload.cc
liblegl_la_SOURCES += lease4_cos.cc
liblegl_la_SOURCES += lease6_cos.cc
liblegl_la_SOURCES += legal_file.cc legal_file.h
liblegl_la_SOURCES += legal_log_log.cc legal_log_log.h
liblegl_la_SOURCES += version.cc

nodist_liblegl_la_SOURCES = legal_log_messages.cc legal_log_messages.h

liblegl_la_CXXFLAGS = $(AM_CXXFLAGS)
liblegl_la_CPPFLAGS = $(AM_CPPFLAGS)
if USE_CLANGPP
# Disable unused parameter warning caused by some of the
# Boost headers when compiling with clang.
liblegl_la_CXXFLAGS += -Wno-unused-parameter
endif

noinst_LTLIBRARIES += libdhcp_legal_log.la

libdhcp_legal_log_la_SOURCES  =
libdhcp_legal_log_la_LDFLAGS  = $(AM_LDFLAGS)
libdhcp_legal_log_la_LDFLAGS  += -avoid-version -export-dynamic -module
# -rpath /nowhere is a hack to trigger libtool to not create a
# convenience archive, resulting in shared modules
libdhcp_legal_log_la_LDFLAGS  += -rpath /nowhere
libdhcp_legal_log_la_LIBADD  = liblegl.la
libdhcp_legal_log_la_LIBADD  += $(top_builddir)/src/lib/hooks/libkea-hooks.la
libdhcp_legal_log_la_LIBADD  += $(top_builddir)/src/lib/log/libkea-log.la
libdhcp_legal_log_la_LIBADD  += $(top_builddir)/src/lib/util/threads/libkea-threads.la
libdhcp_legal_log_la_LIBADD  += $(top_builddir)/src/lib/util/libkea-util.la
libdhcp_legal_log_la_LIBADD  += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libdhcp_legal_log_la_LIBADD  += $(LOG4CPLUS_LIBS)
