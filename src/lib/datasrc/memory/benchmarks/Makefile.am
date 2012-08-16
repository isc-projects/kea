AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(B10_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

noinst_PROGRAMS = rdata_reader_bench

rdata_reader_bench_SOURCES = rdata_reader_bench.cc
rdata_reader_bench_SOURCES += rdata_reader.cc rdata_reader.h

rdata_reader_bench_LDADD = $(top_builddir)/src/lib/datasrc/memory/libdatasrc_memory.la
rdata_reader_bench_LDADD += $(top_builddir)/src/lib/dns/libb10-dns++.la
