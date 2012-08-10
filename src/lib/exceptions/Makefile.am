SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CXXFLAGS=$(B10_CXXFLAGS)

lib_LTLIBRARIES = libb10-exceptions.la
libb10_exceptions_la_SOURCES = exceptions.h exceptions.cc

CLEANFILES = *.gcno *.gcda

libb10_exceptions_includedir = $(includedir)/$(PACKAGE_NAME)/exceptions
libb10_exceptions_include_HEADERS = exceptions.h
