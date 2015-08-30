SUBDIRS = . tests

AM_CPPFLAGS  = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS  = $(KEA_CXXFLAGS)

# Some versions of GCC warn about some versions of Boost regarding
# missing initializer for members in its posix_time.
# https://svn.boost.org/trac/boost/ticket/3477
# But older GCC compilers don't have the flag.
AM_CXXFLAGS += $(WARNING_NO_MISSING_FIELD_INITIALIZERS_CFLAG)

# Define rule to build logging source files from message file
user_chk_messages.h user_chk_messages.cc: s-messages
s-messages: user_chk_messages.mes
	$(top_builddir)/src/lib/log/compiler/message $(top_srcdir)/src/hooks/dhcp/user_chk/user_chk_messages.mes
	touch $@

# Tell automake that the message files are built as part of the build process
# (so that they are built before the main library is built).
BUILT_SOURCES = user_chk_messages.h user_chk_messages.cc

EXTRA_DIST = libdhcp_user_chk.dox
# Ensure that the message file is included in the distribution
EXTRA_DIST += user_chk_messages.mes

# Get rid of generated message files on a clean
CLEANFILES = *.gcno *.gcda user_chk_messages.h user_chk_messages.cc s-messages

# convenience archive

noinst_LTLIBRARIES = libduc.la

libduc_la_SOURCES  =
libduc_la_SOURCES += load_unload.cc
libduc_la_SOURCES += pkt_receive_co.cc
libduc_la_SOURCES += pkt_send_co.cc
libduc_la_SOURCES += subnet_select_co.cc
libduc_la_SOURCES += user.cc user.h
libduc_la_SOURCES += user_chk.h
libduc_la_SOURCES += user_chk_log.cc user_chk_log.h
libduc_la_SOURCES += user_data_source.h
libduc_la_SOURCES += user_file.cc user_file.h
libduc_la_SOURCES += user_registry.cc user_registry.h
libduc_la_SOURCES += version.cc

nodist_libduc_la_SOURCES = user_chk_messages.cc user_chk_messages.h

libduc_la_CXXFLAGS = $(AM_CXXFLAGS)
libduc_la_CPPFLAGS = $(AM_CPPFLAGS)
if USE_CLANGPP
# Disable unused parameter warning caused by some of the
# Boost headers when compiling with clang.
libduc_la_CXXFLAGS += -Wno-unused-parameter
endif

noinst_LTLIBRARIES += libdhcp_user_chk.la

libdhcp_user_chk_la_SOURCES  =
libdhcp_user_chk_la_LDFLAGS  = $(AM_LDFLAGS)
libdhcp_user_chk_la_LDFLAGS  += -avoid-version -export-dynamic -module
# -rpath /nowhere is a hack to trigger libtool to not create a
# convenience archive, resulting in shared modules
libdhcp_user_chk_la_LDFLAGS  += -rpath /nowhere
libdhcp_user_chk_la_LIBADD  = libduc.la
libdhcp_user_chk_la_LIBADD  += $(top_builddir)/src/lib/hooks/libkea-hooks.la
libdhcp_user_chk_la_LIBADD  += $(top_builddir)/src/lib/log/libkea-log.la
libdhcp_user_chk_la_LIBADD  += $(top_builddir)/src/lib/util/threads/libkea-threads.la
libdhcp_user_chk_la_LIBADD  += $(top_builddir)/src/lib/util/libkea-util.la
libdhcp_user_chk_la_LIBADD  += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libdhcp_user_chk_la_LIBADD  += $(LOG4CPLUS_LIBS)
