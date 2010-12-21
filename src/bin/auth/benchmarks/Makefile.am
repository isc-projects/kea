AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/bin -I$(top_builddir)/src/bin
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(B10_CXXFLAGS)

CLEANFILES = *.gcno *.gcda

noinst_PROGRAMS = query_bench
query_bench_SOURCES = query_bench.cc
query_bench_SOURCES += ../auth_srv.h ../auth_srv.cc

query_bench_LDADD = $(top_builddir)/src/lib/dns/libdns++.la
query_bench_LDADD += $(top_builddir)/src/lib/exceptions/libexceptions.la
query_bench_LDADD += $(top_builddir)/src/lib/bench/libbench.la
query_bench_LDADD += $(top_builddir)/src/lib/datasrc/libdatasrc.la
query_bench_LDADD += $(top_builddir)/src/lib/config/libcfgclient.la
query_bench_LDADD += $(top_builddir)/src/lib/cc/libcc.la
query_bench_LDADD += $(top_builddir)/src/lib/xfr/libxfr.la
query_bench_LDADD += $(top_builddir)/src/lib/asiolink/libasiolink.la
query_bench_LDADD += $(SQLITE_LIBS)
