SUBDIRS = . testutils tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES) $(MYSQL_CPPFLAGS)

AM_CXXFLAGS = $(KEA_CXXFLAGS)

CLEANFILES = *.gcno *.gcda

lib_LTLIBRARIES = libkea-mysql.la
libkea_mysql_la_SOURCES  = mysql_connection.cc mysql_connection.h
libkea_mysql_la_SOURCES += mysql_binding.cc mysql_binding.h
libkea_mysql_la_SOURCES += mysql_constants.h

libkea_mysql_la_LIBADD  = $(top_builddir)/src/lib/database/libkea-database.la
libkea_mysql_la_LIBADD += $(top_builddir)/src/lib/cc/libkea-cc.la
libkea_mysql_la_LIBADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libkea_mysql_la_LIBADD += $(top_builddir)/src/lib/log/libkea-log.la
libkea_mysql_la_LIBADD += $(top_builddir)/src/lib/util/libkea-util.la
libkea_mysql_la_LIBADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libkea_mysql_la_LIBADD += $(LOG4CPLUS_LIBS) $(BOOST_LIBS)

libkea_mysql_la_LDFLAGS = -no-undefined -version-info 26:0:0

libkea_mysql_la_LDFLAGS += $(MYSQL_LIBS)

# Specify the headers for copying into the installation directory tree.
libkea_mysql_includedir = $(pkgincludedir)/mysql
libkea_mysql_include_HEADERS = \
	mysql_binding.h \
	mysql_connection.h \
	mysql_constants.h
