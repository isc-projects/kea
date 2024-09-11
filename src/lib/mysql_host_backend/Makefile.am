SUBDIRS = . tests

AM_CXXFLAGS = $(KEA_CXXFLAGS)

CLEANFILES = *.gcno *.gcda

lib_LTLIBRARIES = libkea-mysql-host-backend.la

libkea_mysql_host_backend_la_SOURCES = mysql_host_data_source.cc mysql_host_data_source.h

libkea_mysql_host_backend_la_LIBADD = $(top_builddir)/src/lib/mysql/libkea-mysql.la

libkea_mysql_host_backend_la_LDFLAGS = $(MYSQL_LIBS)

# Specify the headers for copying into the installation directory tree.
libkea_mysql_host_backend_includedir = $(pkgincludedir)/mysql_host_backend

libkea_mysql_host_backend_include_HEADERS = \
        mysql_host_data_source.h
