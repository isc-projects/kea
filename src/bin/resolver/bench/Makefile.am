AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/lib/dns -I$(top_srcdir)/src/bin
AM_CPPFLAGS += -I$(top_builddir)/src/lib/cc
AM_CPPFLAGS += -I$(top_builddir)/src/bin/resolver
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(B10_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

noinst_PROGRAMS = resolver-bench

resolver_bench_SOURCES = main.cc
resolver_bench_SOURCES += fake_resolution.h fake_resolution.cc
resolver_bench_SOURCES += dummy_work.h dummy_work.cc
resolver_bench_SOURCES += naive_resolver.h naive_resolver.cc

resolver_bench_LDADD  = $(GTEST_LDADD)
resolver_bench_LDADD += $(top_builddir)/src/lib/exceptions/libb10-exceptions.la
resolver_bench_LDADD += $(top_builddir)/src/lib/asiolink/libb10-asiolink.la

