AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib

CLEANFILES = *.gcno *.gcda

noinst_PROGRAMS = buffer_bench
buffer_bench_SOURCES = buffer_bench.cc
buffer_bench_LDADD = $(top_builddir)/src/lib/exceptions/libexceptions.la
