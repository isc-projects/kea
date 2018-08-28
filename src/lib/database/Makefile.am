SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(KEA_CXXFLAGS)

lib_LTLIBRARIES = libkea-database.la
libkea_database_la_SOURCES  = database_connection.cc database_connection.h
libkea_database_la_SOURCES += db_exceptions.h
libkea_database_la_SOURCES += db_log.cc db_log.h

libkea_database_la_LIBADD  = $(top_builddir)/src/lib/log/libkea-log.la
libkea_database_la_LIBADD += $(top_builddir)/src/lib/log/interprocess/libkea-log_interprocess.la
libkea_database_la_LIBADD += $(top_builddir)/src/lib/util/threads/libkea-threads.la
libkea_database_la_LIBADD += $(top_builddir)/src/lib/util/libkea-util.la
libkea_database_la_LIBADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libkea_database_la_LIBADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libkea_database_la_LIBADD += $(LOG4CPLUS_LIBS) $(BOOST_LIBS)

libkea_database_la_LDFLAGS = -no-undefined -version-info 0:0:0

# The message file should be in the distribution.
#EXTRA_DIST = config_backend.dox

CLEANFILES = *.gcno *.gcda

# Specify the headers for copying into the installation directory tree.
#libkea_cb_includedir = $(pkgincludedir)/config
#libkea_cb_include_HEADERS = 
