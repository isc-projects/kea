SUBDIRS = . tests

AM_CPPFLAGS  = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS  = $(B10_CXXFLAGS)

# Some versions of GCC warn about some versions of Boost regarding
# missing initializer for members in its posix_time.
# https://svn.boost.org/trac/boost/ticket/3477
# But older GCC compilers don't have the flag.
AM_CXXFLAGS += $(WARNING_NO_MISSING_FIELD_INITIALIZERS_CFLAG)

# Until logging in dynamically loaded libraries is fixed,
# Define rule to build logging source files from message file
# user_chk_messages.h user_chk_messages.cc: s-messages

# Until logging in dynamically loaded libraries is fixed, exclude these.
# s-messages: user_chk_messages.mes
#	$(top_builddir)/src/lib/log/compiler/message $(top_srcdir)/src/hooks/dhcp/user_chk/user_chk_messages.mes
#	touch $@

# Tell automake that the message files are built as part of the build process
# (so that they are built before the main library is built).
# BUILT_SOURCES = user_chk_messages.h user_chk_messages.cc
BUILT_SOURCES =

# Ensure that the message file is included in the distribution
EXTRA_DIST =

# Get rid of generated message files on a clean
#CLEANFILES = *.gcno *.gcda user_chk_messages.h user_chk_messages.cc s-messages
CLEANFILES = *.gcno *.gcda

lib_LTLIBRARIES = libdhcp_user_chk.la
libdhcp_user_chk_la_SOURCES  =
libdhcp_user_chk_la_SOURCES += load_unload.cc
libdhcp_user_chk_la_SOURCES += pkt_receive_co.cc
libdhcp_user_chk_la_SOURCES += pkt_send_co.cc
libdhcp_user_chk_la_SOURCES += subnet_select_co.cc
libdhcp_user_chk_la_SOURCES += user.cc user.h
libdhcp_user_chk_la_SOURCES += user_chk.h
# Until logging in dynamically loaded libraries is fixed, exclude these.
#libdhcp_user_chk_la_SOURCES += user_chk_log.cc user_chk_log.h
libdhcp_user_chk_la_SOURCES += user_data_source.h
libdhcp_user_chk_la_SOURCES += user_file.cc user_file.h
libdhcp_user_chk_la_SOURCES += user_registry.cc user_registry.h
libdhcp_user_chk_la_SOURCES += version.cc

# Until logging in dynamically loaded libraries is fixed, exclude these.
#nodist_libdhcp_user_chk_la_SOURCES = user_chk_messages.cc user_chk_messages.h

libdhcp_user_chk_la_CXXFLAGS = $(AM_CXXFLAGS)
libdhcp_user_chk_la_CPPFLAGS = $(AM_CPPFLAGS) $(LOG4CPLUS_INCLUDES)
libdhcp_user_chk_la_LDFLAGS  = $(AM_LDFLAGS)
libdhcp_user_chk_la_LDFLAGS  += -avoid-version -export-dynamic -module
libdhcp_user_chk_la_LIBADD  =
libdhcp_user_chk_la_LIBADD  += $(top_builddir)/src/lib/hooks/libb10-hooks.la
libdhcp_user_chk_la_LIBADD  += $(top_builddir)/src/lib/log/libb10-log.la
libdhcp_user_chk_la_LIBADD  += $(top_builddir)/src/lib/exceptions/libb10-exceptions.la
libdhcp_user_chk_la_LIBADD  += $(top_builddir)/src/lib/util/libb10-util.la
libdhcp_user_chk_la_LIBADD  += $(top_builddir)/src/lib/util/threads/libb10-threads.la


if USE_CLANGPP
# Disable unused parameter warning caused by some of the
# Boost headers when compiling with clang.
libdhcp_user_chk_la_CXXFLAGS += -Wno-unused-parameter
endif
