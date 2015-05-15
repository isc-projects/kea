SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

if HAVE_GTEST

TESTS = libstats_unittests

libstats_unittests_SOURCES  = run_unittests.cc
libstats_unittests_SOURCES += observation_unittest.cc
libstats_unittests_SOURCES += context_unittest.cc
libstats_unittests_SOURCES += stats_mgr_unittest.cc

libstats_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
libstats_unittests_LDFLAGS  = $(AM_LDFLAGS)  $(GTEST_LDFLAGS)
libstats_unittests_CXXFLAGS = $(AM_CXXFLAGS)

libstats_unittests_LDADD  = $(top_builddir)/src/lib/stats/libkea-stats.la
libstats_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
libstats_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
libstats_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
libstats_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libstats_unittests_LDADD += $(GTEST_LDADD)

endif

noinst_PROGRAMS = $(TESTS)
