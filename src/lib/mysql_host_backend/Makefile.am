SUBDIRS = . tests

AM_CPPFLAGS  = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += $(MYSQL_CPPFLAGS)

AM_CXXFLAGS = $(KEA_CXXFLAGS)

CLEANFILES = *.gcno *.gcda

lib_LTLIBRARIES = libkea-mysql-host-backend.la

libkea_mysql_host_backend_la_SOURCES = mysql_host_data_source.cc mysql_host_data_source.h

libkea_mysql_host_backend_la_LIBADD = $(top_builddir)/src/lib/mysql/libkea-mysql.la
libkea_mysql_host_backend_la_LIBADD += $(top_builddir)/src/lib/database/libkea-database.la
libkea_mysql_host_backend_la_LIBADD += $(top_builddir)/src/lib/cc/libkea-cc.la
libkea_mysql_host_backend_la_LIBADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libkea_mysql_host_backend_la_LIBADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
libkea_mysql_host_backend_la_LIBADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
libkea_mysql_host_backend_la_LIBADD += $(top_builddir)/src/lib/log/libkea-log.la
libkea_mysql_host_backend_la_LIBADD += $(top_builddir)/src/lib/util/libkea-util.la
libkea_mysql_host_backend_la_LIBADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libkea_mysql_host_backend_la_LIBADD += $(LOG4CPLUS_LIBS) $(CRYPTO_LIBS) $(BOOST_LIBS)

libkea_mysql_host_backend_la_LDFLAGS = $(MYSQL_LIBS)

# Specify the headers for copying into the installation directory tree.
libkea_mysql_host_backend_includedir = $(pkgincludedir)/mysql_host_backend

libkea_mysql_host_backend_include_HEADERS = \
        mysql_host_data_source.h
