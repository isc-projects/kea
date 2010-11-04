AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(B10_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

noinst_PROGRAMS = rdatarender_bench
rdatarender_bench_SOURCES = rdatarender_bench.cc

rdatarender_bench_LDADD = $(top_builddir)/src/lib/dns/libdns++.la
rdatarender_bench_LDADD += $(top_builddir)/src/lib/exceptions/libexceptions.la
rdatarender_bench_LDADD += $(SQLITE_LIBS)
