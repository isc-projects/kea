SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CXXFLAGS=$(KEA_CXXFLAGS)

lib_LTLIBRARIES = libkea-exceptions.la

libkea_exceptions_la_SOURCES = exceptions.h exceptions.cc
libkea_exceptions_la_SOURCES += isc_assert.h
libkea_exceptions_la_LDFLAGS = -no-undefined -version-info 2:0:2

CLEANFILES = *.gcno *.gcda

libkea_exceptions_includedir = $(pkgincludedir)/exceptions
libkea_exceptions_include_HEADERS = exceptions.h
libkea_exceptions_include_HEADERS += isc_assert.h
