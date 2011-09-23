AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/bin -I$(top_builddir)/src/bin
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(B10_CXXFLAGS)

CLEANFILES = *.gcno *.gcda

noinst_PROGRAMS = query_bench
query_bench_SOURCES = query_bench.cc
query_bench_SOURCES += ../query.h  ../query.cc
query_bench_SOURCES += ../auth_srv.h ../auth_srv.cc
query_bench_SOURCES += ../auth_config.h ../auth_config.cc
query_bench_SOURCES += ../statistics.h ../statistics.cc
query_bench_SOURCES += ../auth_log.h ../auth_log.cc
# This is a temporary workaround for #1206, where the InMemoryClient has been
# moved to an ldopened library. We could add that library to LDADD, but that
# is nonportable. When #1207 is done this becomes moot anyway, and the
# specific workaround is not needed anymore, so we can then remove this
# line again.
query_bench_SOURCES += ${top_srcdir}/src/lib/datasrc/memory_datasrc.cc

nodist_query_bench_SOURCES = ../auth_messages.h ../auth_messages.cc

query_bench_LDADD = $(top_builddir)/src/lib/dns/libdns++.la
query_bench_LDADD += $(top_builddir)/src/lib/util/libutil.la
query_bench_LDADD += $(top_builddir)/src/lib/exceptions/libexceptions.la
query_bench_LDADD += $(top_builddir)/src/lib/bench/libbench.la
query_bench_LDADD += $(top_builddir)/src/lib/datasrc/libdatasrc.la
query_bench_LDADD += $(top_builddir)/src/lib/config/libcfgclient.la
query_bench_LDADD += $(top_builddir)/src/lib/cc/libcc.la
query_bench_LDADD += $(top_builddir)/src/lib/xfr/libxfr.la
query_bench_LDADD += $(top_builddir)/src/lib/log/liblog.la
query_bench_LDADD += $(top_builddir)/src/lib/nsas/libnsas.la
query_bench_LDADD += $(top_builddir)/src/lib/asiodns/libasiodns.la
query_bench_LDADD += $(top_builddir)/src/lib/asiolink/libasiolink.la
query_bench_LDADD += $(top_builddir)/src/lib/server_common/libserver_common.la
query_bench_LDADD += $(SQLITE_LIBS)

