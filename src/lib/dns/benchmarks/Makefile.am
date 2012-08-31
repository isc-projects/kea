AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(B10_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

noinst_PROGRAMS = rdatarender_bench message_renderer_bench

rdatarender_bench_SOURCES = rdatarender_bench.cc

rdatarender_bench_LDADD = $(top_builddir)/src/lib/dns/libb10-dns++.la
rdatarender_bench_LDADD += $(top_builddir)/src/lib/util/libb10-util.la
rdatarender_bench_LDADD += $(top_builddir)/src/lib/exceptions/libb10-exceptions.la

message_renderer_bench_SOURCES = message_renderer_bench.cc
message_renderer_bench_SOURCES += oldmessagerenderer.h oldmessagerenderer.cc
message_renderer_bench_LDADD = $(top_builddir)/src/lib/dns/libb10-dns++.la
message_renderer_bench_LDADD += $(top_builddir)/src/lib/util/libb10-util.la
message_renderer_bench_LDADD += $(top_builddir)/src/lib/exceptions/libb10-exceptions.la
