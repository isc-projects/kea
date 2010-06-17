AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/bin -I$(top_builddir)/src/bin

CLEANFILES = *.gcno *.gcda

noinst_PROGRAMS = query_bench
if HAVE_BOOST_SYSTEM
noinst_PROGRAMS += netio_bench
endif
query_bench_SOURCES = query_bench.cc
query_bench_SOURCES += ../auth_srv.h ../auth_srv.cc
query_bench_SOURCES += ../normalquestion.h ../normalquestion.cc
query_bench_SOURCES += ../rbt_datasrc.h ../rbt_datasrc.cc
query_bench_SOURCES += ../loadzone.h ../loadzone.cc

query_bench_LDADD = $(top_builddir)/src/lib/dns/libdns.la
query_bench_LDADD += $(top_builddir)/src/lib/exceptions/libexceptions.la
query_bench_LDADD += $(top_builddir)/src/lib/bench/libbench.la
query_bench_LDADD += $(top_builddir)/src/lib/datasrc/libdatasrc.la
query_bench_LDADD += $(top_builddir)/src/lib/config/libcfgclient.la
query_bench_LDADD += $(top_builddir)/src/lib/cc/libcc.a
query_bench_LDADD += $(SQLITE_LIBS)
if HAVE_BOOST_SYSTEM
query_bench_LDFLAGS = $(AM_LDFLAGS) $(BOOST_LDFLAGS)
query_bench_LDADD += $(BOOST_SYSTEM_LIB)
endif

if HAVE_BOOST_SYSTEM
netio_bench_SOURCES = netio_bench.cc
netio_bench_LDFLAGS = $(AM_LDFLAGS) $(BOOST_LDFLAGS)
netio_bench_LDADD = $(top_builddir)/src/lib/exceptions/.libs/libexceptions.a
netio_bench_LDADD += $(BOOST_SYSTEM_LIB)
endif
