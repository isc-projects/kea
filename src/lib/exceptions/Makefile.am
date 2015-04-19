SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CXXFLAGS = $(KEA_CXXFLAGS) $(SHLIB_CXXFLAGS)

lib_LTLIBRARIES = libkea-exceptions.la
libkea_exceptions_la_SOURCES = api.h exceptions.h exceptions.cc

CLEANFILES = *.gcno *.gcda

libkea_exceptions_includedir = $(includedir)/$(PACKAGE_NAME)/exceptions
libkea_exceptions_include_HEADERS = exceptions.h
