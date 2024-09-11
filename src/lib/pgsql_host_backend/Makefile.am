SUBDIRS = . tests

AM_CXXFLAGS = $(KEA_CXXFLAGS)

CLEANFILES = *.gcno *.gcda

lib_LTLIBRARIES = libkea-pgsql-host-backend.la

libkea_pgsql_host_backend_la_SOURCES = pgsql_host_data_source.cc pgsql_host_data_source.h

libkea_pgsql_host_backend_la_LIBADD = $(top_builddir)/src/lib/pgsql/libkea-pgsql.la

libkea_pgsql_host_backend_la_LDFLAGS = $(PGSQL_LIBS)

# Specify the headers for copying into the installation directory tree.
libkea_pgsql_host_backend_includedir = $(pkgincludedir)/pgsql_host_backend

libkea_pgsql_host_backend_include_HEADERS = \
        pgsql_host_data_source.h
