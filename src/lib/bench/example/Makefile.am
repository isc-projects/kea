AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib

CLEANFILES = *.gcno *.gcda

noinst_PROGRAMS = search_bench
search_bench_SOURCES = search_bench.cc

search_bench_LDADD = $(top_builddir)/src/lib/exceptions/libexceptions.la

