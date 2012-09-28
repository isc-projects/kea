AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/bin -I$(top_builddir)/src/bin
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(B10_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

noinst_PROGRAMS = query_bench
query_bench_SOURCES = query_bench.cc
query_bench_SOURCES += ../query.h  ../query.cc
query_bench_SOURCES += ../auth_srv.h ../auth_srv.cc
query_bench_SOURCES += ../auth_config.h ../auth_config.cc
query_bench_SOURCES += ../statistics.h ../statistics.cc
query_bench_SOURCES += ../auth_log.h ../auth_log.cc

nodist_query_bench_SOURCES = ../auth_messages.h ../auth_messages.cc

query_bench_LDADD = $(top_builddir)/src/lib/dns/libb10-dns++.la
query_bench_LDADD += $(top_builddir)/src/lib/util/libb10-util.la
query_bench_LDADD += $(top_builddir)/src/lib/exceptions/libb10-exceptions.la
query_bench_LDADD += $(top_builddir)/src/lib/bench/libb10-bench.la
query_bench_LDADD += $(top_builddir)/src/lib/datasrc/libb10-datasrc.la
query_bench_LDADD += $(top_builddir)/src/lib/config/libb10-cfgclient.la
query_bench_LDADD += $(top_builddir)/src/lib/cc/libb10-cc.la
query_bench_LDADD += $(top_builddir)/src/lib/xfr/libb10-xfr.la
query_bench_LDADD += $(top_builddir)/src/lib/log/libb10-log.la
query_bench_LDADD += $(top_builddir)/src/lib/nsas/libb10-nsas.la
query_bench_LDADD += $(top_builddir)/src/lib/asiolink/libb10-asiolink.la
query_bench_LDADD += $(top_builddir)/src/lib/server_common/libb10-server-common.la
query_bench_LDADD += $(top_builddir)/src/lib/asiodns/libb10-asiodns.la
query_bench_LDADD += $(SQLITE_LIBS)

