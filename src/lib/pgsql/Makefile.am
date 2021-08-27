SUBDIRS = . testutils tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES) $(PGSQL_CPPFLAGS)

AM_CXXFLAGS = $(KEA_CXXFLAGS)

CLEANFILES = *.gcno *.gcda

lib_LTLIBRARIES = libkea-pgsql.la
libkea_pgsql_la_SOURCES  = pgsql_connection.cc pgsql_connection.h
libkea_pgsql_la_SOURCES += pgsql_exchange.cc pgsql_exchange.h


libkea_pgsql_la_LIBADD  = $(top_builddir)/src/lib/database/libkea-database.la
libkea_pgsql_la_LIBADD += $(top_builddir)/src/lib/cc/libkea-cc.la
libkea_pgsql_la_LIBADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libkea_pgsql_la_LIBADD += $(top_builddir)/src/lib/log/libkea-log.la
libkea_pgsql_la_LIBADD += $(top_builddir)/src/lib/util/libkea-util.la
libkea_pgsql_la_LIBADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libkea_pgsql_la_LIBADD += $(LOG4CPLUS_LIBS) $(BOOST_LIBS)

libkea_pgsql_la_LDFLAGS = -no-undefined -version-info 20:0:0

libkea_pgsql_la_LDFLAGS += $(PGSQL_LIBS)

# Specify the headers for copying into the installation directory tree.
libkea_pgsql_includedir = $(pkgincludedir)/pgsql
libkea_pgsql_include_HEADERS = \
	pgsql_connection.h \
	pgsql_exchange.h
