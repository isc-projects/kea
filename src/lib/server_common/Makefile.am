SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS = $(B10_CXXFLAGS)

# Some versions of GCC warn about some versions of Boost regarding
# missing initializer for members in its posix_time.
# https://svn.boost.org/trac/boost/ticket/3477
# But older GCC compilers don't have the flag.
AM_CXXFLAGS += $(WARNING_NO_MISSING_FIELD_INITIALIZERS_CFLAG)

if USE_CLANGPP
# clang++ complains about unused function parameters in some boost header
# files.
AM_CXXFLAGS += -Wno-unused-parameter
endif

lib_LTLIBRARIES = libb10-server-common.la
libb10_server_common_la_SOURCES = client.h client.cc
libb10_server_common_la_SOURCES += keyring.h keyring.cc
libb10_server_common_la_SOURCES += portconfig.h portconfig.cc
libb10_server_common_la_SOURCES += logger.h logger.cc
libb10_server_common_la_SOURCES += socket_request.h socket_request.cc
nodist_libb10_server_common_la_SOURCES = server_common_messages.h
nodist_libb10_server_common_la_SOURCES += server_common_messages.cc
libb10_server_common_la_LIBADD = $(top_builddir)/src/lib/exceptions/libb10-exceptions.la
libb10_server_common_la_LIBADD += $(top_builddir)/src/lib/asiolink/libb10-asiolink.la
libb10_server_common_la_LIBADD += $(top_builddir)/src/lib/cc/libb10-cc.la
libb10_server_common_la_LIBADD += $(top_builddir)/src/lib/config/libb10-cfgclient.la
libb10_server_common_la_LIBADD += $(top_builddir)/src/lib/log/libb10-log.la
libb10_server_common_la_LIBADD += $(top_builddir)/src/lib/acl/libb10-acl.la
libb10_server_common_la_LIBADD += $(top_builddir)/src/lib/dns/libb10-dns++.la
libb10_server_common_la_LIBADD += $(top_builddir)/src/lib/util/io/libb10-util-io.la
BUILT_SOURCES = server_common_messages.h server_common_messages.cc
server_common_messages.h server_common_messages.cc: server_common_messages.mes
	$(top_builddir)/src/lib/log/compiler/message $(top_srcdir)/src/lib/server_common/server_common_messages.mes

EXTRA_DIST = server_common_messages.mes

CLEANFILES = *.gcno *.gcda server_common_messages.h server_common_messages.cc
