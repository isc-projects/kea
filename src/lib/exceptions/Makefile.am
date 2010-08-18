SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CXXFLAGS=$(B10_CXXFLAGS)

lib_LTLIBRARIES = libexceptions.la
libexceptions_la_SOURCES = exceptions.h exceptions.cc

CLEANFILES = *.gcno *.gcda

libexceptions_includedir = $(includedir)/exceptions
libexceptions_include_HEADERS = exceptions.h
