SUBDIRS = . tests

AM_CXXFLAGS = $(KEA_CXXFLAGS)

CLEANFILES = *.gcno *.gcda

lib_LTLIBRARIES = libkea-pgsql-lease-backend.la

libkea_pgsql_lease_backend_la_SOURCES = pgsql_lease_mgr.cc pgsql_lease_mgr.h

libkea_pgsql_lease_backend_la_LIBADD = $(top_builddir)/src/lib/pgsql/libkea-pgsql.la

libkea_pgsql_lease_backend_la_LDFLAGS = $(PGSQL_LIBS)

# Specify the headers for copying into the installation directory tree.
libkea_pgsql_lease_backend_includedir = $(pkgincludedir)/pgsql_lease_backend

libkea_pgsql_lease_backend_include_HEADERS = \
        pgsql_lease_mgr.h
