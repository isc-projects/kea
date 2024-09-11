SUBDIRS = . tests

AM_CXXFLAGS = $(KEA_CXXFLAGS)

CLEANFILES = *.gcno *.gcda

lib_LTLIBRARIES = libkea-mysql-lease-backend.la

libkea_mysql_lease_backend_la_SOURCES = mysql_lease_mgr.cc mysql_lease_mgr.h

libkea_mysql_lease_backend_la_LIBADD = $(top_builddir)/src/lib/mysql/libkea-mysql.la

libkea_mysql_lease_backend_la_LDFLAGS = $(MYSQL_LIBS)

# Specify the headers for copying into the installation directory tree.
libkea_mysql_lease_backend_includedir = $(pkgincludedir)/mysql_lease_backend

libkea_mysql_lease_backend_include_HEADERS = \
        mysql_lease_mgr.h
