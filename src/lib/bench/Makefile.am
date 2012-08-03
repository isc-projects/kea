SUBDIRS = . tests example

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS = $(B10_CXXFLAGS)

CLEANFILES = *.gcno *.gcda

noinst_LTLIBRARIES = libb10-bench.la
libb10_bench_la_SOURCES = benchmark_util.h benchmark_util.cc
EXTRA_DIST = benchmark.h
