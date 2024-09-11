SUBDIRS = . tests

AM_CPPFLAGS  = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += $(PGSQL_CPPFLAGS)

AM_CXXFLAGS = $(KEA_CXXFLAGS)

CLEANFILES = *.gcno *.gcda

lib_LTLIBRARIES = libkea-pgsql-host-backend.la

libkea_pgsql_host_backend_la_SOURCES = pgsql_host_data_source.cc pgsql_host_data_source.h

libkea_pgsql_host_backend_la_LIBADD = $(top_builddir)/src/lib/pgsql/libkea-pgsql.la
libkea_pgsql_host_backend_la_LIBADD += $(top_builddir)/src/lib/database/libkea-database.la
libkea_pgsql_host_backend_la_LIBADD += $(top_builddir)/src/lib/cc/libkea-cc.la
libkea_pgsql_host_backend_la_LIBADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libkea_pgsql_host_backend_la_LIBADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
libkea_pgsql_host_backend_la_LIBADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
libkea_pgsql_host_backend_la_LIBADD += $(top_builddir)/src/lib/log/libkea-log.la
libkea_pgsql_host_backend_la_LIBADD += $(top_builddir)/src/lib/util/libkea-util.la
libkea_pgsql_host_backend_la_LIBADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libkea_pgsql_host_backend_la_LIBADD += $(LOG4CPLUS_LIBS) $(CRYPTO_LIBS) $(BOOST_LIBS)

libkea_pgsql_host_backend_la_LDFLAGS = $(PGSQL_LIBS)

# Specify the headers for copying into the installation directory tree.
libkea_pgsql_host_backend_includedir = $(pkgincludedir)/pgsql_host_backend

libkea_pgsql_host_backend_include_HEADERS = \
        pgsql_host_data_source.h
