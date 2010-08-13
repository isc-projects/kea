SUBDIRS = . tests example

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CXXFLAGS = $(B10_CXXFLAGS)

CLEANFILES = *.gcno *.gcda

lib_LTLIBRARIES = libbench.la
libbench_la_SOURCES = benchmark_util.h benchmark_util.cc
EXTRA_DIST = benchmark.h
